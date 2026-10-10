# Assignment 2: Sample package and Git workflow

## Aim
Create a sample package, host it in a Git repository, check out a file,
modify it, and push the changes again.

## Package
`foss-temperature-demo` is a Python package that converts temperatures.
It requires Python 3.9 or later and has no runtime dependencies.

Run the example from this directory:

```sh
python3 example.py
```

Optional installation in a virtual environment:

```sh
python3 -m venv .venv
.venv/bin/python -m pip install .
```

## Repository
- Hosting service: GitHub (Git is the version-control system).
- Repository: https://github.com/abishekkvh/College
- Branch: `assignment-2-sample-package`
- Package directory: `Semester 5/Free Open Source Software/Assignment-2`

The initial commit provides Celsius-to-Fahrenheit conversion. The second
commit adds Fahrenheit-to-Celsius conversion after checking out the source file.

## Git procedure performed

A separate worktree was created from `origin/main` to preserve unrelated local
changes. The following commands show the two-stage workflow (paths are relative
to the repository root):

```sh
git fetch origin main
git worktree add -b assignment-2-sample-package /tmp/foss-assignment-2-worktree origin/main
cd /tmp/foss-assignment-2-worktree
# Create the package files.
git add -- "Semester 5/Free Open Source Software/Assignment-2"
git commit -m "Add sample Python temperature conversion package"
git push -u origin assignment-2-sample-package

# Check out the tracked file from the current commit before editing it.
git checkout HEAD -- "Semester 5/Free Open Source Software/Assignment-2/temperature_demo/converter.py"
# Add fahrenheit_to_celsius, update the public exports and example,
# and change the package version from 0.1.0 to 0.2.0.
git diff -- "Semester 5/Free Open Source Software/Assignment-2"
git add -- "Semester 5/Free Open Source Software/Assignment-2"
git commit -m "Add Fahrenheit-to-Celsius conversion after file checkout"
git push origin assignment-2-sample-package
```

`git checkout HEAD -- <file>` restores that file from the current commit;
it does not lock it. Run it before making edits you want to keep.

## Expected output

```text
25 C = 77.0 F
98.6 F = 37.0 C
```

## Inspect the history

```sh
git log --oneline -2 assignment-2-sample-package
git diff assignment-2-sample-package~1 assignment-2-sample-package -- "Semester 5/Free Open Source Software/Assignment-2"
```

The initial package commit is `313a073`. The next commit contains the checked-out
file's modification and the updated usage example.
