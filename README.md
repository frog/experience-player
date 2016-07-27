Installation Player
-------------------

# Requirements

Open Frameworks 0.9.3

# Setup

Change the header file path in Project.xconfig:

            #include "<your path>/of_v0.9.3_osx_release/libs/openFrameworksCompiled/project/osx/CoreOF.xcconfig"

Add "addons" to your search paths:

            Build Settings > Header Search Paths > click plus sign "<your path>of_v0.9.3_osx_release/addons/ofxXmlSettings/libs"
            Build Settings > Header Search Paths > click plus sign "<your path>of_v0.9.3_osx_release/addons/ofxXmlSettings/src"

Add "addon" source files ot your Compile Sources:
            
            Build Phases > Compile Sources > click on plus sign > add other > navigate to addon .cpp files
            Repeat for all required addons; ofxXmlSettings



---

## Troubleshooting ##

### How to fix your build ###


** Step 1:  Identify the previous user's open frameworks path. **  

That's a required piece of information to make this work quickly.


For us, as I'm writing this, the previous users's (relative) path is:

    ../../_platform/open_frameworks/of_v0.9.3_osx_release
    
    
You'll need to modify this in two places:

    Project.xcconfig

(up next)

and
    
    frogPlayer.xcodeproj/project.pbxproj

(instructions below)

** Step 2: Project.xcconfig **

Open _Project.xcconfig_ in your favorite text editor.

Line 3: OF_PATH  - set this to your open frameworks path, RELATIVE TO THIS DIRECTORY

example:

my installation-video-player lives in /Users/anderson.miller/Documents/installation-video-player

my openframeworks installation lives in /Users/anderson.miller/Documents/of_v0.9.3_osx_release

So, I change line 3 to:

    OF_PATH = ../of_v0.9.3_osx_release

Now, **Line 6**

I set that one to:

    #include "/Users/anderson.miller/Documents/of_v0.9.3_osx_release/libs/openFrameworksCompiled/project/osx/CoreOF.xcconfig"
    
(pretty much the same deal, use my path and not the one that's already there).

** Step 3: The XCode Project ** 

(this step has to happen on the command line)
Set two environment variables.

    export PREVIOUS="..\/..\/_platform\/open_frameworks\/of_v0.9.3_osx_release"
    export NEW="..\/of_v0.9.3_osx_release"

Now you're going to run a regex on the project file:


    cat frogPlayer.xcodeproj/project.pbxproj | sed s/$PREVIOUS/$NEW/g > temp.xml
    mv temp.xml frogPlayer.xcodeproj/project.pbxproj


**You should be able to open and use the project successfully now!**

**Please do not commit either of those files moving forward if you did this!**
