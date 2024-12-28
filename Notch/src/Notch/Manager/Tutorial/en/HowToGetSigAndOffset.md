# How to get signatures/offsets needed for update

Requirements: IDA/Ghidra + CheatEngine

To get some initial understanding, I recommend reading this, even tho it's incomplete as of now: https://frederoxdev.github.io/Bedrock-Modding-Wiki/

How to check sigs:
1. Open CheatEngine
2. Open Minecraft and connect CheatEngine to it
3. In CheatEngine's search panel set them as follows: instead of "All", choose Minecraft.Windows.exe, Writable - uncheck, Executable - check, Scan Type - Array of byte
4. Now you're ready to scan!
5. Paste sig in "Array of byte" textbox and scan it, if 1 result found - sig is good

### GuiData::displayClientMessage:
You can try just searching for this sig that leads to the func call directly that worked from 1.20.3X to 1.21.2:
"E8 ?? ?? ?? ?? 90 48 85 DB 74 09 48 8B CB E8 ?? ?? ?? ?? 90 48 89 7D C7 48 8B 4D CF 48 89 7D CF 48 85 C9 74 09 E8 ?? ?? ?? ?? 48 8B 7D CF 48 85 FF 74 09"

If it didnt work:
1. Open IDA/Ghidra
2. Search for bytes and input "persona.emote.easter_egg" or "persona.emote.chat_message" there, search
3. When result found, xref to first function
5. Then switch to pseudocode
6. On lines 114-117 find 3 arg function, that if you go into starts with a bunch aXX = 0 at the start

###  Player::playerInventory & PlayerInventory::inventory
48 8b 91 (? ? ? ?) Player::playerInventory 80 ba ? ? ? ? ? 75 ? 48 8b 8a (? ? ? ?) PlayerInventory::inventory 8b 52 ? 48 8b 01 48 8b 40 ? 48 ff 25 ? ? ? ? 48 8d 05
48 8b 91 ? ? ? ? 80 ba ? ? ? ? ? 75 ? 48 8b 8a ? ? ? ? 8b 52 ? 48 8b 01 48 8b 40 ? 48 ff 25 ? ? ? ? 48 8d 05
Could also be used:
48 8b ? (? ? ? ?) 80 ba ? ? ? ? ? 75 ? 48 8b 8a (? ? ? ?) ?

Gives a million results but 99% of what it has is correct offsets

### Player::gamemode
48 8b b5 ? ? ? ? 48 8b 06 48 8b 78 ? 48 8b 01 // 1.20.3X+
49 8b 9e ? ? ? ? 48 8b 03 4c 8d 4c 24 // 1.20.3X+
48 8b 8b ? ? ? ? 45 84 f6 74 ? 45 84 e4
4c 8b b0 ? ? ? ? 49 8b 06 4c 8b b8
48 8b 88 ? ? ? ? 48 8d 54 24 ? c6 80

### Actor::hurtTime
8b 86 ? ? ? ? 85 c0 7e ? ff c8 89 86 ? ? ? ? 48 8b 96 // 1.20.3X+
44 8b 87 ? ? ? ? b8 ? ? ? ? 41 f7 e8 // 1.20.3X+
89 86 ? ? ? ? 48 8b 96 ? ? ? ? 48 83 fa // 1.20.3X+
c7 81 ? ? ? ? 0A 00 00 00 48 8b 81 // 2 results, 1st one is the one, 1.20.3X+
c7 81 ? ? ? ? 0A 00 00 00 48 8b 81 ? ? ? ? 48 85 c0 0f 84 ? ? ? ? c7 00 // more direct one

### Actor::level
48 8b 8f ? ? ? ? 48 8b 11 48 8b 82 ? ? ? ? ff 15 ? ? ? ? 48 8b 8f // 1.20.3X+
48 8b 8e ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 48 8b 10 // 1.20.3X+
48 8b 8e ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 48 8b 08 48 89 8b // 1.20.3X+
49 8b 8f ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 84 c0 75 // 1.20.3X+

4d 8b 81 ? ? ? ? 48 8b 42 ? 48 85 c0
49 83 be ? ? ? ? ? 0f 84 ? ? ? ? 48 8b 86

### Actor::categories
f6 87 ? ? ? ? ? 74 ? 41 0f 28 c2 // 1.20.3X+
f6 83 ? ? ? ? ? 74 ? 48 8b cb // 1.20.3X+
8b 81 ? ? ? ? d1 e8 a8 ? 48 0f 45 f9 // 1.20.3X+
8b 87 ? ? ? ? d1 e8 a8 ? 0f 84 ? ? ? ? 48 8b 17 // 1.20.3X+
8b 83 ? ? ? ? d1 e8 a8 ? 74 ? 80 bb // 1.20.3X+

f6 87 ? ? ? ? ? 0f 84 ? ? ? ? 4c 8b b7
8b 88 ? ? ? ? 0f 29 b4 24 ? ? ? ? 0f 28 35

### Level::getPlayerMap
aka Level::getPlayerList
Find getRuntimeActorList using method in sigs section
Add 0xB8 to 1st arg getRuntimeActorList gets called with and you get the offset

### Level::hitResult
// for newer versions
48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c0 ? 48 83 c4 - gives multiple results, last one is the correct one
48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c0 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc 48 8d 81 ? ? ? ? c3 cc cc cc cc cc cc cc cc 40 53
48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc 48 83 ec ? 48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c0 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc 48 8d 81

### Gamemode::lastBreakProgress
4d 89 66 ? 49 8b 8e // 1.20.3X+
89 46 ? 80 be

### ScreenView::VisualTree
4c 8b 43 ? 49 8b 08 48 8b 41
48 8b 49 ? 48 8b 01 48 8b 40 ? ff 15 ? ? ? ? 84 c0 0f 84 ? ? ? ? 45 32 ff
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ff 15 ? ? ? ? 84 c0 74 ? 48 8b 4f ? 83 61 ? ? 48 8b 4f ? 48 8b 01 48 8b 40 ? ff 15 ? ? ? ? 66 0f 1f 84 00
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ff 15 ? ? ? ? 84 c0 74 ? 48 8b 4f ? 83 61 ? ? 4c 8b 87
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ff 15 ? ? ? ? 84 c0 74 ? 48 8b 4f ? 83 61 ? ? 48 8b 4f ? 48 8b 01 48 8b 40 ? ff 15 ? ? ? ? 48 8b 4f
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ff 15 ? ? ? ? 84 c0 74 ? 48 8b b7
4c 8b 47 ? 49 8b 08 48 8b 41 ? ba
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ff 15 ? ? ? ? 84 c0 75 ? 48 8b 4f ? 48 8b 41 ? 48 39 41 ? 75 ? 48 8b 81 ? ? ? ? 48 39 81 ? ? ? ? 75 ? 48 8b 81 ? ? ? ? 48 39 81 ? ? ? ? 75 ? 80 b9

### Actor::runtimeID / EntityContext::id (EntityId) + EntityContext::basicReg
Found near getActorFlag first param is basicReg, second is runtimeID

# Sigs to functions

### ItemRenderer::renderGuiItemNew
textures/entity/shulker/shulker_
xref out 1 time, then xref to last func and here you go

### Level::getRuntimeActorList
48 89 5C 24 18 55 56 57 48 83 EC 40 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 38 48 8B F2 48 8B E9 48 89
xref out and here u go
or scan 40 53 48 83 EC 30 48 81 (1.21.30+) first res should be it

### HudCursorRenderer::render
look for textures/ui/cross_hair or ui_crosshair, first function should be it

### ItemRenderer::render
Look for this number 0x80100240C00

### HudMobEffectsRenderer::render
textures/ui/hud_mob_effect_background