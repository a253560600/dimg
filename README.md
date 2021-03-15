# dimg

This repository contains a copy of the digiKam (https://www.digikam.org) source code,
with the core dimg libs and some relevant plugins extracted for standalone use in other programs.

This means that modifications were made to the code and the build system such that only these core dimg libs and
plugins are built. The original git history and all the now unused source files are kept (but won't be built) to make it easier
to keep this repo in sync with the original digiKam sources. This may change in the future.

It is not possible to build digiKam from this repo - only dimg and relevant libs can be built,
by using the CMakeLists.txt in the repository root folder.

The QtWidgets dependency was removed from the extracted libs, so this can be used both with
QtWidgets and QML applications.

Note: This repo does not contain the full digiKam history, only from the last digiKam commit before the changes onwards.
This is because the full history contains files >100MB and GitHub rejects the push due to a retarded file size limitation.
Of course this makes it harder to sync digiKam changes with this repo and ruins the nice commit history. Fuck you, GitHub.

When syncing this repo with digiKam changes, make sure that any relevant changes in the digiKam build system are also applied
to the CMakeLists.txt in the root folder.

# TODO

* Example application/QML element for rendering dimg
* Finish implementation of shims
* Make it possible for dynamicthread to use a user-defined QThreadPool instead of the global one
* Re-add the red eye removal plugin (difficult because it relies on the new face recognition engine that has a lot of other deps)
* Restore commented KMemoryInfo usage (only used to check if there is enough free memory when loading dimgs, not important)
