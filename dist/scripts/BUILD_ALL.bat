@echo off
echo **Steping to mode root directory
cd ..
echo **Checking PapyrusSourcesDD sources and tools from GitHub
if not exist "PapyrusSourcesDD" (echo **Sources not present, clonning from GitHub & git clone https://github.com/IHateMyKite/PapyrusSourcesDD) else (echo **PapyrusSourcesDD Folder already present, skipping...)
cd PapyrusSourcesDD
echo **Starting compilation of all PAPYRUS scripts
BUILD & PAUSE