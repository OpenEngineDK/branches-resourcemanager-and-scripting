
#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

#ifndef ISCRIPTRESOURCE_H
#define ISCRIPTRESOURCE_H

namespace OpenEngine {
	namespace Resources {

		using namespace std;

class IScriptResource {


public:
    IScriptResource() {};

	// virtual metode til running code

};


/**
 * Resource smart pointer.
 */
typedef boost::shared_ptr<IScriptResource> IScriptResourcePtr;


class IScriptResourcePlugin {
private:
	list<string> languages;
	
public:
	virtual ~IScriptResourcePlugin() {};

	virtual IScriptResourcePtr CreateResource() = 0;

	void AddLanguage(string lang) {
		languages.push_back(lang);
	};

	bool RunsLanguage(string lang) {
		for (list<string>::iterator itr = languages.begin(); itr != languages.end(); itr++ ) {
			if ( (*itr) == lang) {
				return true;
			}
		}
		return false;
	};

};

class IScriptModule {

private:
	list<string> languages;
	
public:
	virtual ~IScriptModule() {};

	virtual void Init() = 0;

	void AddLanguage(string lang) {
		languages.push_back(lang);
	};

	bool RunsLanguage(string lang) {
		for (list<string>::iterator itr = languages.begin(); itr != languages.end(); itr++ ) {
			if ( (*itr) == lang) {
				return true;
			}
		}
		return false;
	};

};

	}
}


#endif // ISCRIPTRESOURCE_H
