#ifndef FORM_H
#define FORM_H

#include "global.h"

#include "drawable.h"
#include "entity_manager.h"
#include "object_manager.h"
#include "states_manager.h"

#include <string>

namespace Baukasten {
	class LogicalSpace;
	class VirtualSpace;

	class BAUKASTEN_EXPORT Form : public Drawable,
	public EntityManager, public ObjectManager, public StatesManager {
	public:
		Form( const std::string& );
		virtual ~Form();

		void addLSpace( const std::string&, LogicalSpace* );
		void removeLSpace( const std::string& );
		void addToLSpace( const std::string&, Entity* );
		void removeFromLSpace( const std::string&, const std::string& );
		bool hasLSpace( const std::string& ) const;
		LogicalSpace* getLSpace( const std::string& ) const;

		void addVSpace( const std::string&, VirtualSpace* );
		void removeVSpace( const std::string& );
		void addToVSpace( const std::string&, Drawable* );
		void removeFromVSpace( const std::string&, const std::string& );
		bool hasVSpace( const std::string& ) const;
		VirtualSpace* getVSpace( const std::string& ) const;

	protected:
		std::string mMeshName;

		std::map<const std::string, LogicalSpace*> mLSpaces;
		std::map<const std::string, VirtualSpace*> mVSpaces;

		EntityMap   mSpaceMap;
	};
}

#endif // FORM_H

