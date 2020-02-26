# Higurashi Retinaizer

Enables retina display support for Higurashi games on macOS.  May also work on other games that use the same unity version as one of the Higurashi games

## Compiling
Compile with `make`

## Installation
Copy the compiled `libRetinaizer.dylib` to `HigurashiGame.app/Contents/Frameworks/MonoEmbedRuntime/osx/`.  You will need a version of `Assembly-CSharp.dll` that has [this commit](https://github.com/07th-mod/higurashi-assembly/commit/0f625a5bcebdb07674531b92eb68f8d16a9bc14f) in it.

Alternatively, you can run your game with the environment variable `DYLD_INSERT_LIBRARIES` set to `libRetinaizer.dylib`, for example `DYLD_INSERT_LIBRARIES=/path/to/libRetinaizer.dylib HigurashiGame.app/Contents/MacOS/HigurashiGame`

If you find that your game does not retinaize, open your Unity log (`~/Library/Logs/Unity/Player.log`) and search it for `libRetinaizer`.  If anything comes up, it should contain a reason for not loading (or a claim that it tried to enable retina, in which case there's an issue with the library).  If nothing comes up, you messed up the loading of the dylib and should verify that you followed the above steps correctly.

## Compatible Games / Unity Versions
- Onikakushi, Watanagashi (Unity 5.2.2f1)
- Tatarigoroshi (Unity 5.3.4p1 and 5.4.0f1)
- Himatsubushi (Unity 5.4.1f1)
- Meakashi (Unity 5.5.3p1)
- Tsumihoroboshi (Unity 5.5.3p3)
- Minagoroshi (Unity 5.6.7f1)

## Known Issues
- If you start the game in fullscreen and then defullscreen with the green window button (rather than an in-game control), the window will be way too big
- Game screen resolutions are used as pixel resolutions, not display-independent-point resolutions (so 1280x720 will now make a tiny window).  It seemed like less work to do things this way rather than the other way.

## Development
To ease development and debugging, use of Xcode is recommended.

Create a new Xcode project and select Library.  Then set the framework to Cocoa and the type to Dynamic.  Delete the `.h` and `.m` files it defaults to, and drag all the files into the Xcode file manager, making sure to uncheck `Copy items if needed`.  Under the project settings Build Phases → Link Binaries with Libraries tab, add the Cocoa, Carbon, and OpenGL frameworks.  Build once, then add a new build scheme and edit the `Executable` to be the target game, and set the `DYLD_INSERT_LIBRARIES` to the dylib product (probably something like `/Users/you/Library/Developer/Xcode/DerivedData/something/...`).  Now you can run with ⌘R and breakpoints will work as expected. 

Note: Tatarigoroshi crashes on fullscreen and defullscreen when run under lldb (and therefore also when run through xcode).  Don't think that's due to the retinaizer and spend large amounts of time trying to debug it.
