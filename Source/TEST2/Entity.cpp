#include "Entity.h"
#include "message/Packet.h"
#include "message/game.pb.h"

using namespace message;
Entity::Entity()
{
	static auto _W_C_ENTITY = [&](::google::protobuf::Message* _packet) {
		auto packet = (W_C_ENTITY*)(_packet);
		if (!packet) {
			return false;
		}


		return true;
	};

	REGISTER_PACKET(new W_C_ENTITY(), _W_C_ENTITY);
}