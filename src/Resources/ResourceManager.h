// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <Resources/ITextureResource.h>
#include <Resources/IModelResource.h>
#include <Resources/IShaderResource.h>
#include <Resources/IScriptResource.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <iostream>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Resource manager.
 *
 * @class ResourceManager ResourceManager.h Resources/ResourceManager.h
 */
class ResourceManager {
private:
    static list<string> paths;
	static map<string, string> pathcache;

    static vector<ITextureResourcePlugin*>  texturePlugins;
    static map<string, ITextureResourcePtr> textures;

    static vector<IModelResourcePlugin*>    modelPlugins;
    static map<string, IModelResourcePtr>   models;

    static vector<IShaderResourcePlugin*>   shaderPlugins;
    static map<string, IShaderResourcePtr>  shaders;

	static vector<IScriptResourcePlugin*>   scriptPlugins;
	static vector<IScriptModule*>           scriptModules;

public:
    static void AppendPath(string);
    static void PrependPath(string);
    static bool IsInPath(string);
    static string FindFileInPath(string);

    static void AddTexturePlugin(ITextureResourcePlugin* plugin);
    static void AddModelPlugin(IModelResourcePlugin* plugin);
    static void AddShaderPlugin(IShaderResourcePlugin* plugin);
	static void AddScriptPlugin(IScriptResourcePlugin* plugin);
	static void AddScriptModule(IScriptModule* module);

	static ITextureResourcePtr CreateTexture(const string filename);
	static IModelResourcePtr   CreateModel(const string filename);
    static IShaderResourcePtr  CreateShader(const string filename);
	static IScriptResourcePtr CreateScript(const string language);
	static vector<IScriptModule*> GetScriptModules(const string language);

	static void Shutdown();
};

} // NS Resources
} // NS OpenEngine

#endif // _RESOURCE_MANAGER_H_
