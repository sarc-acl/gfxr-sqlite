/********************************************************************************
    Copyright 2026 The Sokatoa Project Authors

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        https://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
********************************************************************************/

#include "apidump_json.h"

#include <array>
#include <cstdio>
#include <fstream>
#include <vector>
#include <zlib.h>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

namespace
{

/** Reads a hexadecimal or decimal integer out of a recorded value string.
 *
 * Handles are written as "0xb400006f93b9d120" and plain integers as decimal, so both spellings
 * turn up in address fields.
 */
bool ParseRecordedInteger(std::string_view text, uint64_t& out)
{
    size_t index = 0;
    while ((index < text.size()) && (text[index] == ' '))
    {
        ++index;
    }

    uint64_t value = 0;
    bool     any   = false;

    if (((index + 1) < text.size()) && (text[index] == '0') && ((text[index + 1] == 'x') || (text[index + 1] == 'X')))
    {
        index += 2;
        while (index < text.size())
        {
            const char c = text[index];
            uint64_t   digit;

            if ((c >= '0') && (c <= '9'))
            {
                digit = static_cast<uint64_t>(c - '0');
            }
            else if ((c >= 'a') && (c <= 'f'))
            {
                digit = static_cast<uint64_t>(c - 'a') + 10;
            }
            else if ((c >= 'A') && (c <= 'F'))
            {
                digit = static_cast<uint64_t>(c - 'A') + 10;
            }
            else
            {
                break;
            }

            value = (value * 16) + digit;
            any   = true;
            ++index;
        }
    }
    else
    {
        while ((index < text.size()) && (text[index] >= '0') && (text[index] <= '9'))
        {
            value = (value * 10) + static_cast<uint64_t>(text[index] - '0');
            any   = true;
            ++index;
        }
    }

    if (!any)
    {
        return false;
    }

    out = value;
    return true;
}

/** Finds a child of `container` whose "name" field matches, or nullptr. */
const nlohmann::json* FindNamed(const nlohmann::json* container, std::string_view wanted)
{
    if ((container == nullptr) || !container->is_array())
    {
        return nullptr;
    }

    for (const auto& child : *container)
    {
        if (!child.is_object())
        {
            continue;
        }

        const auto name = child.find("name");
        if ((name != child.end()) && name->is_string() &&
            (name->get_ref<const std::string&>() == wanted))
        {
            return &child;
        }
    }

    return nullptr;
}

} // namespace

//
// ApiDumpNode
//

bool ApiDumpNode::IsUnusedPlaceholder() const
{
    return (StringField("value") == "UNUSED") && (StringField("address") == "UNUSED");
}

bool ApiDumpNode::HasField(const char* field) const
{
    return (node_ != nullptr) && node_->is_object() && (node_->find(field) != node_->end());
}

std::string_view ApiDumpNode::StringField(const char* field) const
{
    if ((node_ == nullptr) || !node_->is_object())
    {
        return {};
    }

    const auto found = node_->find(field);
    if ((found == node_->end()) || !found->is_string())
    {
        return {};
    }

    return found->get_ref<const std::string&>();
}

ApiDumpNode ApiDumpNode::Member(std::string_view member_name) const
{
    if ((node_ == nullptr) || !node_->is_object())
    {
        return {};
    }

    const auto members = node_->find("members");
    if (members == node_->end())
    {
        return {};
    }

    return ApiDumpNode(FindNamed(&(*members), member_name));
}

uint64_t ApiDumpNode::Address() const
{
    // The placeholder spellings ("address", "UNUSED", "NULL") all fail to parse, which is the
    // answer we want: no usable capture address was recorded.
    uint64_t address = 0;
    if (!ParseRecordedInteger(StringField("address"), address))
    {
        return 0;
    }

    return address;
}

size_t ApiDumpNode::ElementCount() const
{
    if ((node_ == nullptr) || !node_->is_object())
    {
        return 0;
    }

    const auto elements = node_->find("elements");
    if ((elements == node_->end()) || !elements->is_array())
    {
        return 0;
    }

    return elements->size();
}

ApiDumpNode ApiDumpNode::ElementAt(size_t index) const
{
    if ((node_ == nullptr) || !node_->is_object())
    {
        return {};
    }

    const auto elements = node_->find("elements");
    if ((elements == node_->end()) || !elements->is_array() || (index >= elements->size()))
    {
        return {};
    }

    return ApiDumpNode(&(*elements)[index]);
}

bool ApiDumpNode::ElementIsScalar(size_t index) const
{
    const ApiDumpNode element = ElementAt(index);
    return element.IsPresent() && !element.node_->is_object();
}

std::string_view ApiDumpNode::ElementScalar(size_t index) const
{
    const ApiDumpNode element = ElementAt(index);
    if (!element.IsPresent())
    {
        return {};
    }

    if (element.node_->is_string())
    {
        return element.node_->get_ref<const std::string&>();
    }

    // An object shaped element carries its scalar in "value".
    return element.ValueString();
}

//
// ApiDumpCall
//

bool ApiDumpCall::IsAnnotation() const
{
    return (call_ != nullptr) && (call_->find("annotation") != call_->end());
}

std::string_view ApiDumpCall::Name() const
{
    if (call_ == nullptr)
    {
        return {};
    }

    const auto name = call_->find("name");
    if ((name == call_->end()) || !name->is_string())
    {
        return {};
    }

    return name->get_ref<const std::string&>();
}

uint64_t ApiDumpCall::ThreadId() const
{
    if (call_ == nullptr)
    {
        return 0;
    }

    const auto thread = call_->find("thread");
    if ((thread == call_->end()) || !thread->is_string())
    {
        return 0;
    }

    // Recorded as "Thread 1"; the trailing integer is all we need, and gfxreconstruct treats
    // thread ids as opaque.
    uint64_t id = 0;
    const std::string& text = thread->get_ref<const std::string&>();
    size_t             pos  = text.find_last_of(' ');
    if (pos == std::string::npos)
    {
        return 0;
    }

    if (!ParseRecordedInteger(std::string_view(text).substr(pos + 1), id))
    {
        return 0;
    }

    return id;
}

std::optional<uint64_t> ApiDumpCall::CommandNumber() const
{
    if (call_ == nullptr)
    {
        return std::nullopt;
    }

    const auto command_number = call_->find("commandNumber");
    if ((command_number == call_->end()) || !command_number->is_string())
    {
        return std::nullopt;
    }

    uint64_t id = 0;
    if (!ParseRecordedInteger(command_number->get_ref<const std::string&>(), id))
    {
        return std::nullopt;
    }

    return id;
}

ApiDumpNode ApiDumpCall::Arg(std::string_view arg_name) const
{
    if (call_ == nullptr)
    {
        return {};
    }

    const auto args = call_->find("args");
    if (args == call_->end())
    {
        return {};
    }

    return ApiDumpNode(FindNamed(&(*args), arg_name));
}

ApiDumpNode ApiDumpCall::ReturnValue() const
{
    if (call_ == nullptr)
    {
        return {};
    }

    const auto value = call_->find("returnValue");
    if (value == call_->end())
    {
        return {};
    }

    return ApiDumpNode(&(*value));
}

std::string_view ApiDumpCall::ReturnTypeName() const
{
    if (call_ == nullptr)
    {
        return {};
    }

    const auto type = call_->find("returnType");
    if ((type == call_->end()) || !type->is_string())
    {
        return {};
    }

    return type->get_ref<const std::string&>();
}

//
// ApiDumpReader
//

namespace
{

/** SAX handler that materialises one call object at a time.
 *
 * The document is `[ { "frameNumber": "0", "isSetupFrame"?: true, "apiCalls": [ {call}, ... ] },
 * ... ]`. "isSetupFrame" is only present when always_dump_setup recorded a frame outside the
 * capture range. Events outside a call only move the state machine along; events inside one are
 * accumulated into a small DOM which is handed to the call handler and then discarded, so peak
 * memory tracks the largest single call rather than the file.
 */
class ApiDumpSaxHandler
{
  public:
    ApiDumpSaxHandler(
        const ApiDumpReader::FrameBeginHandler& on_frame_begin,
        const ApiDumpReader::CallHandler&       on_call,
        const ApiDumpReader::FrameEndHandler&   on_frame_end,
        uint64_t&                               call_count
    ) :
        on_frame_begin_(on_frame_begin), on_call_(on_call), on_frame_end_(on_frame_end),
        call_count_(call_count)
    {}

    const std::string& GetError() const { return error_; }

    // nlohmann SAX interface.

    bool null() { return InCall() ? AddValue(nlohmann::json(nullptr)) : true; }

    bool boolean(bool value)
    {
        if (InCall())
        {
            return AddValue(nlohmann::json(value));
        }

        if (state_ == State::kExpectIsSetupFrame)
        {
            is_setup_frame_ = value;
            state_          = State::kInFrame;
        }

        return true;
    }

    bool number_integer(int64_t value) { return InCall() ? AddValue(nlohmann::json(value)) : true; }

    bool number_unsigned(uint64_t value) { return InCall() ? AddValue(nlohmann::json(value)) : true; }

    bool number_float(double value, const std::string&)
    {
        return InCall() ? AddValue(nlohmann::json(value)) : true;
    }

    bool string(std::string& value)
    {
        if (InCall())
        {
            return AddValue(nlohmann::json(value));
        }

        if (state_ == State::kExpectFrameNumber)
        {
            uint64_t frame_number = 0;
            if (!ParseRecordedInteger(value, frame_number))
            {
                error_ = "frameNumber \"" + value + "\" is not a number";
                return false;
            }

            frame_number_      = frame_number;
            have_frame_number_ = true;
            state_             = State::kInFrame;
        }

        return true;
    }

    bool binary(nlohmann::json::binary_t& value)
    {
        return InCall() ? AddValue(nlohmann::json(std::move(value))) : true;
    }

    bool start_object(size_t)
    {
        if (InCall())
        {
            return PushContainer(nlohmann::json::object());
        }

        if (state_ == State::kInCallsArray)
        {
            // The start of a call. Everything from here until its matching end_object is DOM'd.
            call_depth_ = 1;
            call_root_  = nlohmann::json::object();
            stack_.clear();
            stack_.push_back(&call_root_);
            return true;
        }

        if (state_ == State::kInTopArray)
        {
            state_             = State::kInFrame;
            have_frame_number_ = false;
            frame_number_      = 0;
            is_setup_frame_    = false;
            return true;
        }

        return true;
    }

    bool key(std::string& value)
    {
        if (InCall())
        {
            pending_key_ = value;
            return true;
        }

        if (state_ == State::kInFrame)
        {
            if (value == "frameNumber")
            {
                state_ = State::kExpectFrameNumber;
            }
            else if (value == "isSetupFrame")
            {
                state_ = State::kExpectIsSetupFrame;
            }
            else if (value == "apiCalls")
            {
                if (!have_frame_number_)
                {
                    // Attributing calls to the wrong frame would be silent and hard to spot later,
                    // so refuse instead.
                    error_ = "apiCalls appeared before frameNumber, which the reader relies on";
                    return false;
                }

                // Fired here, rather than as soon as frameNumber's value is read, so that
                // isSetupFrame - which the layer writes after frameNumber but before apiCalls -
                // has already been seen.
                on_frame_begin_(frame_number_, is_setup_frame_);
                state_ = State::kExpectCallsArray;
            }
        }

        return true;
    }

    bool end_object()
    {
        if (InCall())
        {
            if (stack_.size() > 1)
            {
                stack_.pop_back();
                return true;
            }

            // Closing the call object itself.
            stack_.clear();
            call_depth_ = 0;
            ++call_count_;
            on_call_(ApiDumpCall(&call_root_));
            return true;
        }

        if (state_ == State::kInFrame)
        {
            if (have_frame_number_)
            {
                on_frame_end_(frame_number_);
            }

            state_ = State::kInTopArray;
        }

        return true;
    }

    bool start_array(size_t)
    {
        if (InCall())
        {
            return PushContainer(nlohmann::json::array());
        }

        if (state_ == State::kExpectCallsArray)
        {
            state_ = State::kInCallsArray;
            return true;
        }

        if (state_ == State::kStart)
        {
            state_ = State::kInTopArray;
            return true;
        }

        return true;
    }

    bool end_array()
    {
        if (InCall())
        {
            if (!stack_.empty())
            {
                stack_.pop_back();
            }
            return true;
        }

        if (state_ == State::kInCallsArray)
        {
            state_ = State::kInFrame;
            return true;
        }

        if (state_ == State::kInTopArray)
        {
            state_ = State::kDone;
        }

        return true;
    }

    bool parse_error(size_t position, const std::string&, const nlohmann::json::exception& ex)
    {
        error_ = "parse error at byte " + std::to_string(position) + ": " + ex.what();
        return false;
    }

  private:
    enum class State
    {
        kStart,
        kInTopArray,
        kInFrame,
        kExpectFrameNumber,
        kExpectIsSetupFrame,
        kExpectCallsArray,
        kInCallsArray,
        kDone
    };

    bool InCall() const { return call_depth_ > 0; }

    /** Attaches a finished scalar to the container currently on top of the stack. */
    bool AddValue(nlohmann::json&& value)
    {
        if (stack_.empty())
        {
            return true;
        }

        nlohmann::json* top = stack_.back();
        if (top->is_object())
        {
            (*top)[pending_key_] = std::move(value);
        }
        else
        {
            top->push_back(std::move(value));
        }

        return true;
    }

    /** Attaches a new container and makes it the current one. */
    bool PushContainer(nlohmann::json&& container)
    {
        if (stack_.empty())
        {
            return true;
        }

        nlohmann::json* top = stack_.back();
        nlohmann::json* added;

        if (top->is_object())
        {
            (*top)[pending_key_] = std::move(container);
            added                = &(*top)[pending_key_];
        }
        else
        {
            top->push_back(std::move(container));
            added = &top->back();
        }

        stack_.push_back(added);
        return true;
    }

    const ApiDumpReader::FrameBeginHandler& on_frame_begin_;
    const ApiDumpReader::CallHandler&       on_call_;
    const ApiDumpReader::FrameEndHandler&   on_frame_end_;
    uint64_t&                               call_count_;

    State    state_{ State::kStart };
    uint64_t frame_number_{ 0 };
    bool     have_frame_number_{ false };
    bool     is_setup_frame_{ false };

    int                          call_depth_{ 0 };
    nlohmann::json               call_root_;
    std::vector<nlohmann::json*> stack_;
    std::string                  pending_key_;

    std::string error_;
};

/** Gzip's 2-byte magic number (RFC 1952). */
constexpr unsigned char kGzipMagic[2] = { 0x1f, 0x8b };

/** Whether path's content is gzip-compressed, detected by content rather than extension: the
 * Sokatoa host's ApiDump.CompressGzip preference decides this per capture, but never changes the
 * .apidump file name, so callers can't tell from the path alone (mirrors how the .apidump JSON
 * itself is only ever recognized by extension in isApiDumpFile - this is the one place that
 * additionally has to look inside the file).
 */
bool IsGzipFile(const std::string& path)
{
    std::ifstream probe(path, std::ios::binary);
    if (!probe.is_open())
    {
        return false;
    }
    unsigned char header[2] = { 0, 0 };
    probe.read(reinterpret_cast<char*>(header), sizeof(header));
    return (static_cast<size_t>(probe.gcount()) == sizeof(header)) && (header[0] == kGzipMagic[0]) &&
           (header[1] == kGzipMagic[1]);
}

/** A minimal std::streambuf that decompresses a gzip file on the fly via zlib's whole-file gzip
 * API, so ApiDumpReader::Read can hand nlohmann::json::sax_parse a plain istream regardless of
 * whether the underlying file is gzip-compressed or plain text.
 */
class GzipStreambuf : public std::streambuf
{
  public:
    explicit GzipStreambuf(const std::string& path) : file_(gzopen(path.c_str(), "rb")) {}

    ~GzipStreambuf() override
    {
        if (file_ != nullptr)
        {
            gzclose(file_);
        }
    }

    GzipStreambuf(const GzipStreambuf&)            = delete;
    GzipStreambuf& operator=(const GzipStreambuf&) = delete;

    bool IsOpen() const { return file_ != nullptr; }

  protected:
    int_type underflow() override
    {
        if (file_ == nullptr)
        {
            return traits_type::eof();
        }
        const int bytes_read = gzread(file_, buffer_.data(), static_cast<unsigned int>(buffer_.size()));
        if (bytes_read <= 0)
        {
            return traits_type::eof();
        }
        setg(buffer_.data(), buffer_.data(), buffer_.data() + bytes_read);
        return traits_type::to_int_type(*gptr());
    }

  private:
    gzFile                        file_;
    std::array<char, 64 * 1024> buffer_;
};

} // namespace

bool ApiDumpReader::Read(const std::string& path, std::string& error)
{
    ApiDumpSaxHandler handler(on_frame_begin_, on_call_, on_frame_end_, call_count_);

    // allow_exceptions=false so a truncated capture reports through parse_error instead of
    // throwing. Captures routinely end mid-document because the app is killed to stop the capture.
    auto RunParse = [&handler](std::istream& input) {
        return nlohmann::json::sax_parse(input, &handler, nlohmann::json::input_format_t::json, false);
    };

    bool ok;
    if (IsGzipFile(path))
    {
        GzipStreambuf gzip_streambuf(path);
        if (!gzip_streambuf.IsOpen())
        {
            error = "could not open " + path;
            return false;
        }
        std::istream input(&gzip_streambuf);
        ok = RunParse(input);
    }
    else
    {
        std::ifstream input(path, std::ios::binary);
        if (!input.is_open())
        {
            error = "could not open " + path;
            return false;
        }
        ok = RunParse(input);
    }

    if (!ok)
    {
        error = handler.GetError();
        if (error.empty())
        {
            error = "malformed api dump json";
        }
        return false;
    }

    return true;
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
