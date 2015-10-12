#!/bin/sh
# Modifies the install_name of all the .dylibs to use RPATH

if [ -z "$1" ]; then
	echo "First argument (dylibs dir) must be supplied"
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "Directory \"$1\" doesn't exist!"
	exit 1
fi

cd "$1"
DYLIB_DIR="$PWD"

for dylib in "$DYLIB_DIR"/*.dylib; do
	if [ ! -L "$dylib" ]; then

		new_name=`echo "$dylib" | sed "s|$DYLIB_DIR|@rpath|"`

		# fix LC_ID_DYLIB
		install_name_tool -id "$new_name" "$dylib"
	fi
done

# ORIGINAL
# set -e

# [ -n "$DSTROOT" ] || exit 1
# [ -n "$DEVELOPER_DIR" ] || exit 1

# for dylib in "$DSTROOT""$DEVELOPER_DIR"/usr/lib/*.dylib; do
# 	if [ ! -L "$dylib" ]; then
# 		old_name=`otool -D "$dylib" | sed "1d"`
# 		new_name=`echo "$old_name" | sed "s|$DEVELOPER_DIR|@rpath|"`

# 		# fix LC_ID_DYLIB
# 		install_name_tool -id "$new_name" "$dylib"

# 		# fix LC_LOAD_DYLIB entries in other binaries
# 		for file in "$DSTROOT""$DEVELOPER_DIR"/usr/bin/* "$DSTROOT""$DEVELOPER_DIR"/usr/lib/*.dylib; do
# 			if [ ! -L "$file" ]; then
# 				install_name_tool -change "$old_name" "$new_name" "$file"
# 			fi
# 		done
# 	fi
# done

# for bin in "$DSTROOT""$DEVELOPER_DIR"/usr/bin/*; do
# 	# add LC_RPATH entry
# 	install_name_tool -add_rpath @executable_path/../.. "$bin"
# done