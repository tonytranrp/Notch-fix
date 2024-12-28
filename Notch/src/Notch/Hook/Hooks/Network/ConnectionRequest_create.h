#pragma once

class ConnectionRequest__createHook : public Hook {
public:
	static inline void* detour;
	static void* ConnectionRequestcreateCallback(
        void* result,
        void* userSigner,
        const void* certificate,
        const std::string* selfSignedId,
        const std::string* serverAddress,
        void* clientRandomId,
        const std::string* skinId,
        const void** skinImageData,
        const void** capeImageData,
        const void** bloomData,
        const std::string* skinIID,
        const unsigned int growthLevel,
        const void* serializedSkin,
        const std::string* deviceId,
        void* currentInputMode,
        int uiProfile,
        int guiScale,
        const std::string* languageCode,
        bool isEduMode,
        const std::string* tenantId,
        void* classRole,
        const std::string* platformId,
        const std::string* thirdPartyName,
        char thirdPartyNameOnly,
        const std::string* platformOnlineId,
        const std::string* platformOfflineId,
        std::string* capeId
    ) {
        moduleMgr->onJoiningServer();
        return Memory::CallFunc<void*, void*, void*, const void*, const std::string*, const std::string*, void*, const std::string*, const void**, const void**, const void**, const std::string*, const unsigned int, const void*, const std::string*, void*, int, int, const std::string*, bool, const std::string*, void*, const std::string*, const std::string*, char, const std::string*, const std::string*, std::string*>(detour, result, userSigner, certificate, selfSignedId, serverAddress, clientRandomId, skinId, skinImageData, capeImageData, bloomData, skinIID, growthLevel, serializedSkin, deviceId , currentInputMode, uiProfile, guiScale, languageCode, isEduMode, tenantId, classRole, platformId, thirdPartyName, thirdPartyNameOnly, platformOnlineId, platformOfflineId, capeId);
	}
	virtual void Initialize() {
		Memory::CreateHook(getSig("ConnectionRequest::create"), &ConnectionRequestcreateCallback, &detour, xorstr_("ConnectionRequest::create Hook"));
	}
};