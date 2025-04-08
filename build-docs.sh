#!/bin/bash

doxygen
sphinx-build docs/source/ docs/build/
