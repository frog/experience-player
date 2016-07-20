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

