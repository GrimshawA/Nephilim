This module handles model loading and managing.

It is through its interface that multiple loaders can be defined,
like ASSIMP, FBX SDK and other formats.

Usually, the interface will be implemented under a plugin,
but if the user desires, he can register his custom loader
directly into the content manager, compiled directly into the engine or app.