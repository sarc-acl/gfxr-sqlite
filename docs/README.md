# GFXR Sqlite Database Documentation -- Read-Only Viewer

A self-contained, read-only Excalidraw viewer for schema excalidraw files.

Hosted at: `https://sarc-acl.github.io/gfxr-sqlite/`

## How it works

`index.html` loads React + `@excalidraw/excalidraw@0.18.1` from `esm.sh` via an ESM importmap, fetches the sibling `.excalidraw` JSON, and renders it with `viewModeEnabled` -- panning and zooming work, editing is disabled.

No build step. No `node_modules`. Just static files served by GitHub Pages.

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
