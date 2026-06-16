"""Serve this folder over HTTP and open the viewer in the default browser.

Run with: python hostLocal.py
Stop with Ctrl+C.
"""

from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import sys
import webbrowser

PORT = 8080
HERE = Path(__file__).resolve().parent


def main() -> int:
    handler = partial(SimpleHTTPRequestHandler, directory=str(HERE))
    try:
        server = ThreadingHTTPServer(("127.0.0.1", PORT), handler)
    except OSError as exc:
        print(f"Could not bind to port {PORT}: {exc}", file=sys.stderr)
        print("Another process may be using it. Stop it or edit PORT in this script.", file=sys.stderr)
        return 1

    url = f"http://localhost:{PORT}/"
    print(f"Serving {HERE} at {url}")
    print("Press Ctrl+C to stop.")
    webbrowser.open(url)

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nShutting down.")
    finally:
        server.server_close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
