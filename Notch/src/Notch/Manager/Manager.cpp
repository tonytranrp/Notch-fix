#include "Manager.h"
static std::map<std::string, int> offsets;
static std::map<std::string, size_t> indexes;
static std::map<std::string, void*> signatures;
bool debug = false;
void addOffset(const std::string& functionName, int offset) {
    offsets[functionName] = offset;
    if (debug) {
        std::string message = StringUtil::combine("Offset Added ", functionName, " | ", offset);
        logF(message, "INFO");
    }
}
void addIndex(const std::string& functionName, int index) {
    indexes[functionName] = index;
}
void addSignature(const std::string& functionName, const std::string& signature) {
    signatures[functionName] = Memory::addSignature(signature.c_str());
    if (debug) {
        std::string message = (uintptr_t)signatures[functionName] == 0u ? StringUtil::combine("Signature Not Found ", functionName, " | ", signature) : StringUtil::combine("Signature Found ", functionName, " | ", signature);
        std::string status = (uintptr_t)signatures[functionName] == 0u ? "FAIL" : "OKAY";
        logF(message, status);
    }
}

int getOffset(const std::string& functionName) {
    for (std::pair<std::string, int> offset : offsets) {
        if (functionName == offset.first) {
            return offset.second;
        }
    }
    return 0;
}
size_t getIndex(const std::string& functionName) {
    for (std::pair<std::string, int> index : indexes) {
        if (functionName == index.first) {
            return index.second;
        }
    }
    return 0;
}
void* getSig(const std::string& functionName) {
    auto it = signatures.find(functionName);
    if (it != signatures.end()) {
        return it->second;
    }
    return nullptr;
}
bool Manager::checkVer(std::set<std::string> versionList) {
    return versionList.find(version::GET_VERSION()) != versionList.end();
}
void Manager::init() {
    try {
        auto ver = version::GET_VERSION();
        logF(StringUtil::combine("Ver: ", ver), "INFO");
        logF(StringUtil::combine("Supported 1.21.X: ", StringUtil::join(targetVersions1_21_X, ", ")), "INFO");
        logF(StringUtil::combine("Supported 1.21.2X: ", StringUtil::join(targetVersions1_21_2X, ", ")), "INFO");
        logF(StringUtil::combine("Supported 1.21.3X: ", StringUtil::join(targetVersions1_21_3X, ", ")), "INFO");
        logF(StringUtil::combine("Switching Offset/Signature to ", ver, "..."), "INFO");
        uint64_t start = TimeUtil::getCurrentMs();
        uint64_t inittime = TimeUtil::getCurrentMs() - start;
        logF("Initializing Index...", "WAIT");
        if (Manager::checkVer(Manager::targetVersions1_21_X)) {
            addIndex("ServerPlayer::displayClientMessage", 213);
            addIndex("Level::getRuntimeActorList", 278);
            addIndex("ClientInstance::grabMouse", 332);
            addIndex("ClientInstance::releaseMouse", 333);
        }
        else if (Manager::checkVer(Manager::targetVersions1_21_2X)) {
            addIndex("ServerPlayer::displayClientMessage", 210);
            addIndex("Level::getRuntimeActorList", 279);
            addIndex("ClientInstance::grabMouse", 333);
            addIndex("ClientInstance::releaseMouse", 334); 
        }
        else if (Manager::checkVer(Manager::targetVersions1_21_3X)) {
            addIndex("ServerPlayer::displayClientMessage", 213);
            addIndex("Level::getRuntimeActorList", 280); // idk!! + 1
            addIndex("ClientInstance::grabMouse", 335); // idk!! + 2
            addIndex("ClientInstance::releaseMouse", 336); // idk!! + 2
        }
        inittime = TimeUtil::getCurrentMs() - start;
        logF(StringUtil::combine("Initialized Index in ", inittime, "ms"), "OKAY");
        
        logF("Initializing Offset...", "WAIT");
        if (checkVer(targetVersions1_21_X)) {
            addOffset("ClientInstance::getrefdef", 0x330);
            addOffset("ClientInstance::guiData", 0x558);
            addOffset("ClientInstance::getFovX", 0x6F0);
            addOffset("ClientInstance::getFovY", 0x704);

            addOffset("LevelRendererPlayer::cameraPos", 0x5FC);
            
            addOffset("Actor::getPosition", 0x298);
            addOffset("Actor::getAABB", 0x2A0);
            addOffset("Actor::getRotation", 0x2A8);
            addOffset("Actor::level", 0x250);
          
            addOffset("Player::gamemode", 0xEC8);
            addOffset("Player::getSupplies", 0x760);
           
            addOffset("PlayerInventory::inventory", 0xC0);
        }
        else if (checkVer(targetVersions1_21_2X)) {
            addOffset("ClientInstance::getrefdef", 0x330);
            addOffset("ClientInstance::guiData", 0x558);
            addOffset("ClientInstance::getFovX", 0x6F0);
            addOffset("ClientInstance::getFovY", 0x704);

            addOffset("LevelRendererPlayer::cameraPos", 0x5FC);

            addOffset("Actor::getPosition", 0x270);
            addOffset("Actor::getAABB", 0x298);
            addOffset("Actor::getRotation", 0x2A0);
            addOffset("Actor::level", 0x230);

            addOffset("Player::gamemode", 0xB00);
            addOffset("Player::getSupplies", 0x628);
            addOffset("PlayerInventory::inventory", 0xB8);
        }
        else if (checkVer(targetVersions1_21_3X)) {
            addOffset("ClientInstance::getrefdef", 0x360);
            addOffset("ClientInstance::guiData", 0x588);
            addOffset("ClientInstance::getFovX", 0x720);
            addOffset("ClientInstance::getFovY", 0x734);

            addOffset("LevelRendererPlayer::cameraPos", 0x614);

            addOffset("Actor::getPosition", 0x270);
            addOffset("Actor::getAABB", 0x298);
            addOffset("Actor::getRotation", 0x2A0);
            addOffset("Actor::level", 0x230);

            addOffset("Player::gamemode", 0xB18);
            addOffset("Player::getSupplies", 0x628);

            addOffset("PlayerInventory::inventory", 0xB8);

        };
        inittime = TimeUtil::getCurrentMs() - start;
        logF(StringUtil::combine("Initialized Offset in ", inittime, "ms"), "OKAY");
        
        logF("Initializing Signature...", "WAIT");
        addSignature("GameMode::baseUseItem", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F2 48 8B F9 45 33 F6 4C 89 75 ? 48 8D 4D ? E8 ? ? ? ? 90 48 8B 5F");
        addSignature("GameMode::getDestroyRate", "48 89 5C 24 18 57 48 83 EC 30 48 8B F9 0F 29");
        addSignature("Actor::lerpMotion", "48 83 EC ? 4C 8B 81 ? ? ? ? 4D 85 C0 74 ? 8B 02");
        addSignature("Actor::getNameTag", "48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 ? 48 8B 08 BA ? ? ? ? 48 8B 40 ? 48 2B C1 48 C1 F8 ? 66 3B D0 73 ? 48 8B 41 ? 48 85 C0 74 ? 38 50 ? 75 ? 48 83 C0");
        addSignature("Actor::playEmote", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 0F B6 F8");
        addSignature("BlockSource::getSeenPerscent", "40 55 57 41 54 41 55 41 56 41 57 48 81 EC A8");
        addSignature("Level::tick", "48 89 5c 24 ? 57 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 84 24 ? ? ? ? 48 8b d9 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 48 8d 0d");
        addSignature("MinecraftPackets::createPacket", "E8 ? ? ? ? 90 48 83 BD ? ? 00 00 ? 0F 84 ? ? ? ? ff");
        addSignature("MouseDevice::feed", "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24");
        addSignature("Keyboard::feed", "48 83 ec ? 0f b6 c1 4c 8d 05");
        addSignature("LevelRendererPlayer::bobHurt", "40 53 56 48 83 EC 78 ? ? 7C");
        addSignature("LevelRendererPlayer::getFov", "48 8B C4 48 89 58 18 48 89 70 20 57 48 81 EC 90 00 00 00 0F 29 70 E8 0F 29 78 D8 44");
        addSignature("ScreenView::SetupAndRender", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA");
        addSignature("ClientInstance::update", "48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 54 41 56 41 57 48 8D AC 24 F0 FA FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44");
        addSignature("UIScene::render", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B D9 B9 ? ? ? ?");
        addSignature("Font::drawTransformed", "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 48 89 78 ? 41 54 41 56 41 57 48 81 EC");
        addSignature("Options::getGamma", "48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 48 8B 01 48 8B 40 ? 74 ? 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42 ? 48 83 C4 ? C3 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 75 ? E8 ? ? ? ? CC E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 01");
        // ActorRenderDispatcher::render | String xref: No renderer found - have you set the entity's description:identifier correctly?
        if (checkVer(targetVersions1_21_X)) {
            addSignature("CameraAssignAngle", "8B 44 24 48 89 43 08 C6");
            addSignature("ThirdPersonNameTag", "0f 84 ? ? ? ? 49 8b d6 48 8b ce e8 ? ? ? ? 84 c0 0f 84");
            addSignature("HurtColor", "E8 ? ? ? ? E9 ? ? ? ? 8B 43 ? 48 8D 54 24");
            addSignature("LevelRenderer::renderLevel", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F0");
            addSignature("HudMobEffectRenderer::render", "48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 E0 EE FF FF");
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 48 89 55");
            addSignature("ActorRenderDispatcher::render", "48 89 ? ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? 4D 8B ? 49 8B ? 48 8B ? 4C 8B ? 41 8B");
            addSignature("CameraAvoidanceSystemUtil::calculateHardDistanceConstraint", "40 ? 56 57 48 81 EC ? ? ? ? 44 0F");
        }
        else if (checkVer(targetVersions1_21_2X)) {
            addSignature("CameraAssignAngle", "8B 44 24 48 89 43 08 C6");
            addSignature("ThirdPersonNameTag", "0f 84 ? ? ? ? 49 8b d6 48 8b ce e8 ? ? ? ? 84 c0 0f 84");
            addSignature("HurtColor", "E8 ? ? ? ? E9 ? ? ? ? 8B 43 ? 48 8D 54 24 ? 48 8B 4B ? 89 44 24 ? E8 ? ? ? ? 4C 8B D8");
            addSignature("ItemRenderer::renderGuiItemNew", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 E8 48 81 EC 18 01 00 00 0F 29 B4 24 00 01 00 00 48");
            addSignature("LevelRenderer::renderLevel", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F0 48 8B DA 4C 8B F1");
            addSignature("HudMobEffectRenderer::render", "48 8D 05 ? ? ? ? 48 89 85 ? ? ? ? 48 C7 85 ? ? ? ? ? ? ? ? 0F 28 85 ? ? ? ? 66 0F 7F 85 ? ? ? ? 48 8D 95 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 0F 57 C0 0F 11 85");
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E0");
            addSignature("ActorRenderDispatcher::render", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B F8 48 8B F2");
            addSignature("CameraAvoidanceSystemUtil::calculateHardDistanceConstraint", "40 ? 56 57 48 81 EC ? ? ? ? 44 0F");
        } else if (checkVer(targetVersions1_21_3X)) {
            addSignature("CameraAssignAngle", "F3 0F 11 43 08 C6 43 0C 01");
            addSignature("ThirdPersonNameTag", "0F 84 ? ? ? ? 49 8B D4 49 8B CD");
            addSignature("HurtColor", "E8 ? ? ? ? E9 FD 02 00 00 8B 46 18");
            addSignature("ItemRenderer::renderGuiItemNew", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D8 48 81 EC 28 01 00 00 0F 29 B4 24 10 01 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 00 44");
            addSignature("HudMobEffectRenderer::render", "48 8D 05 ? ? ? ? 48 89 85 ? ? ? ? 48 C7 85 ? ? ? ? ? ? ? ? 0F 28 85 ? ? ? ? 66 0F 7F 85 ? ? ? ? 48 8D 95 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 0F 57 C0");
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E0");
            addSignature("ActorRenderDispatcher::render", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B D8 48 8B FA 4C 8B F9");
        }
        inittime = TimeUtil::getCurrentMs() - start;
        logF(StringUtil::combine("Initialized Signature in ", inittime, "ms"), "OKAY");
    }
    catch (const std::exception& e) {
        logF(e.what(), "ERROR");
    }
}
