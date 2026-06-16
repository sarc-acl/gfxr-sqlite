# GFXR Sqlite Database Documentation -- Read-Only Viewer

A self-contained, read-only Excalidraw viewer for schema excalidraw files.

Hosted at: `https://sarc-acl.github.io/gfxr-sqlite/`

## How it works

`index.html` loads React + `@excalidraw/excalidraw@0.18.1` from `esm.sh` via an ESM importmap, fetches the sibling `.excalidraw` JSON, and renders it with `viewModeEnabled` -- panning and zooming work, editing is disabled.

Below the diagram there is a **SQL query widget**: `index.html` loads `sql.js@1.12.0` (SQLite compiled to WebAssembly) from a CDN, fetches the sibling `demo.sqlite` into an in-memory copy on first use, and runs read-only queries entirely client-side. Queries use the prepared-statement API so column names are shown even when a query returns zero rows. Nothing is sent to a server, and a page refresh restores the original database.

No build step. No `node_modules`. Just static files served by GitHub Pages.

## The demo database

`demo.sqlite` is a small exported GFXR database committed next to `index.html`. The **entire file downloads to the visitor's browser**, so keep it small -- ideally a few MB or less, and well under GitHub's 50 MB warning / 100 MB hard limit. To refresh it, replace `demo.sqlite` with a new export, commit, and push.

## Run locally

Opening `index.html` via `file://` will fail -- browsers block `fetch()` from `file://` origins. Serve the folder over HTTP instead:

```powershell
cd gfxr-db-pages
python -m http.server 8080
# then open http://localhost:8080/
```

Or use the hostLocal.py script.

Any static server works (`npx serve`, `caddy file-server`, etc.).

## Updating the diagram

Replace `GFXRDatabase.excalidraw` or one of the other excalidraw files with the latest export from Excalidraw, commit, and push. 
GitHub Pages redeploys on every push to `main` (typically under a minute). Hard-refresh the page to bypass cache.

## Deployment

See [`deployment-plan.md`](deployment-plan.md) for the full setup and rationale, including version pinning, gotchas, and the GitHub Pages configuration.
