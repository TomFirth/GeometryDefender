#!/usr/bin/env bash
set -e

echo "Geometry Defender Release Packager"
echo "Ensure your release build has been compiled via Android Studio (app:assembleRelease)."

mkdir -p builds

SOURCE_APK="app/build/outputs/apk/release/app-release.apk"
DEST_APK="builds/GeometryDefender_1.0.0.apk"

if [ -f "$SOURCE_APK" ]; then
    cp "$SOURCE_APK" "$DEST_APK"
    echo "Successfully packaged release APK to $DEST_APK"
else
    echo "Error: $SOURCE_APK not found. Please run assembleRelease first."
    exit 1
fi
