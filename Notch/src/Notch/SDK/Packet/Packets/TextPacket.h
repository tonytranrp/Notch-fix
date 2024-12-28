#pragma once

#include "../BasePacket.h"
#include "../../Actor/Actor.h"
#include "../../../Utils/HMath.h"

class TextPacket : public Packet {
public:
	enum class Type : int8_t {
		Raw = 0,
		Chat = 1,
		Translate = 2,
		Popup = 3,
		JukeboxPopup = 4,
		Tip = 5,
		SystemMessage = 6,
		Whisper = 7,
		Announcement = 8,
		TextObjectWhisper = 9,
		TextObject = 10,
	};

	TextPacket() {
		static auto vtable = GetPacketVTable(PacketID::Text);
		this->vTable = vtable;
	}
	TextPacket(Actor* player, std::string message, Type messageType = Type::Chat) : TextPacket() {
		this->player = player;
		this->messageType = messageType;
		this->sourceName = player->getNameTag().c_str();
		this->message = message;
		this->xboxUserId = "";
	}

	Type messageType;
	std::string sourceName;
	std::string message;
private:
	char pad_2[0x18];
public:
	bool translationNeeded = false;
	std::string xboxUserId;
	Actor* player;
	std::string platformChatId;
};