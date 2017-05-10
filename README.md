# DynamicSoundtrackSystem
Made as part of my Complex Game Systems assignment at AIE Sydney. The DynamicSoundtrackSystem is a library that can be built into a C++
application which allows for developers to manipulate audio data to create a dynamic soundtrack. From using simple volume and mute controls,
to advanced DSP filters with custom parameters, developers are able to utilize this library to create a vast number of effects that will
add to the immersion of the game.

## Installation
The library requires a certain FMOD dll at runtime which can be found in the dependencies folder. For debug, copy `fmodL.dll` from the
dependencies folder into your project's working directory. For release, copy `fmod.dll` from the dependencies folder into your  project's 
Release directory.

## Building
Build the project in x86 mode in either debug or release. Once completed, copy the lib file and headers into the dependencies folder of 
your project into a folder with subdirectories of Debug and Release. To be able to use the library in your project, navigate to the 
properties page of your project and do the following:
###### C/C++ -> General -> Additional Include Directories
`$(SolutionDir)dependencies\yourFolderName\$(Configuration)`
###### Linker -> General -> Additional Library Directories
`$(SolutionDir)dependencies\yourFolderName\$(Configuration)`
###### Linker -> Input -> Additional Dependencies
`DynamicSoundtrackSystem.lib`

## Getting Started
The audio manager is a Singleton class so for any operations you’ll need to go through the Instance of the audio manager. Before 
performing any audio operations you’ll need to call the Init function of the audio manager in your startup routine. In your clean-up 
routine run the Shutdown function of the audio manager to clean up allocated memory during the audio manager’s operations. Finally, 
the audio manager has an update method that should be called once per frame during your applications’ update method and passed a deltaTime 
argument.
Accessing any class or method in this library requires you to go through the DSS namespace like so:
```c++
DSS::AudioManager::Instance()->Init();
```

### Include the following headers
- AudioManager.hpp – Audio Manager the core header file that contains most of the necessary operations of the package
-	ChannelManager.hpp – Channel Manager for operations to perform on individual channels.
-	ChannelGroupManager.hpp – Channel Group Manager allows the user to create a ChannelGroup which is an easy way to manage multiple channels 
  for the purposes of grouping relavant sounds and/or multitracking operations
-	Submixer.hpp – Each ChannelGroup contains a submixer class which provides a way for individual channels of a ChannelGroup to have simple 
  mixing operations performed on them.

## Creating Audio Events
The audio manager has realtime audio event capabilities that can manipulate the audio stream through the use of simple mute and 
volume operations, and complex DSP filters that can be fed parameters. The audio manager is also capable of running a large amount of 
these events at once by taking in a vector of an Eventdata structures which can all have their own different event information.

To create an audio event, first create a vector that contains these Eventdata structures. Next create an Eventdata structure and fill 
in the relevant parameters. These structures have default values that are not run by default allowing you to only need to fill in the 
relevant parts that you want activated. Once your Eventdata structure has your desired information, feed it into the vector. 
When you want to run the events, just call the ActivateEvents method of the audio manager and feed in the vector of Eventdata 
structures like so:
```c++
DSS::AudioManager::Instance()->ActivateEvents(myEventsVector);
```
