#ifndef _SCRIPTENTITY_H_
#define _SCRIPTENTITY_H_
#include "ScriptWrapper.h"
#include "prerequisites.h"
#include <BaseEntity.h>

namespace Magnetite
{
	namespace Script 
	{
		/**
		 * @class ScriptEntity
		 * 
		 * Class that wraps callbacks into a script object to allow entities to be defined in script.
		 */
		class ScriptEntity : public BaseEntity
		{
		protected:
			/** 
			 * Persistent Handle on the Script object.
			 */
			PersistentObject mScriptObject;
		public:
			
			ScriptEntity(World* world);
			
			virtual ~ScriptEntity();
			
			/**
			 * Sets the script object
			 */
			void setObject( PersistentObject obj );
			
			virtual void create();
			
			virtual void think(float dt);
		};
	}
};


#endif
