# アップデートに必要なシグネチャー／オフセットの取得方法

必要条件 IDA/Ghidra + CheatEngine

最初の理解を得るために、今のところ不完全ではあるが、これを読むことをお勧めする。https://frederoxdev.github.io/Bedrock-Modding-Wiki/

シグネチャの確認方法
1. CheatEngineを開く。
2. Minecraftを開き、CheatEngineを接続する。
3. CheatEngineの検索パネルで、以下のように設定する。「すべて」の代わりに「Minecraft.Windows.exe」を選択、「書き込み可能」のチェックを外し、「実行可能」のチェックを入れ、「スキャンタイプ」を「バイト配列」にする。
4. これでスキャンの準備ができました！
5. Array of byte "テキストボックスにsigを貼り付けてスキャンする。

### GuiData::displayClientMessage：
1.20.3Xから1.21.2まで動作していたfunc呼び出しに直接つながるこのシグを検索してみてください：
「E8 ?? ?? ?? ?? 90 48 85 db 74 09 48 8b cb e8 ? ?? ?? ?? 90 48 89 7d c7 48 8b 4d cf 48 89 7d cf 48 85 c9 74 09 e8 ? ?? ?? ?? 48 8b 7d cf 48 85 ff 74 09」

うまくいかなかった場合
1. IDA/Ghidraを開く
2. bytesを検索し、そこに 「persona.emote.easter_egg 」または 「persona.emote.chat_message 」を入力して検索する。
3. 結果が見つかったら、最初の関数を参照する。
5. 次に擬似コードに切り替える。
6. 114-117行目で3つの引数関数を見つける。

### Player::getSupplies & PlayerInventory::inventory
48 8b 91 (? ? ?) Player::getSupplies 80 ba ? ? ? ? ? 75 ? 48 8b 8a ( ? ? ? ) PlayerInventory::inventory 8b 52 ? 48 8b 01 48 8b 40 ? 48 ff 25 ? ? ? 48 8d 05
48 8b 91 ? ? ? ? 80 ba ? ? ? ? ? 75 ? 48 8b 8a


### Player::GameMode
48 8b b5 ? ? ? 48 8b 06 48 8b 78 ? 48 8b 01 // 1.20.3X+ ?
49 8b 9e ? ? ? ? 48 8b 03 4c 8d 4c 24 // 1.20.3X+ ?
48 8b 8b ? ? ? ? 45 84 f6 74 ? 45 84 e4
4c 8b b0 ? ? ? 49 8b 06 4c 8b b8
48 8b 88 ? ? ? ? 48 8d 54 24 ? c6 80

### Actor::hurtTime
8b 86 ? ? ? ? 85 c0 7e ? ff c8 89 86 ? ? ? 48 8b 96 // 1.20.3X+ ?
44 8b 87 ? ? ? ? b8 ? ? ? ? 41 f7 e8 // 1.20.3X+ ?
89 86 ? ? ? ? 48 8b 96 ? ? ? ? 48 83 fa // 1.20.3X+ ?
c7 81 ? ? ? ? 0A 00 00 00 48 8b 81 // 2つの結果、1つ目は1.20.3X+のもの。
c7 81 ? ? ? ? 0A 00 00 00 48 8b 81 ? ? ? 48 85 c0 0f 84 ? ? ? c7 00 // より直接的なもの

### Actor::level
48 8b 8f ? ? ? ? 48 8b 11 48 8b 82 ? ? ff 15 ? ? ? ? 48 8b 8f // 1.20.3X+ ?
48 8b 8e ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ff 15 ? ? ? ? 48 8b 10 // 1.20.3X+ ?
48 8b 8e ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ff 15 ? ? ? ? 48 8b 08 48 89 8b // 1.20.3X+ ?
49 8b 8f ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ff 15 ? ? ? ? 84 c0 75 // 1.20.3X+ ?

4d 8b 81 ? ? ? 48 8b 42 ? 48 85 c0
49 83 be ? ? ? ? ? 0f 84 ? ? ? ? 48 8b 86

### Actor::categories
f6 87 ? ? ? ? ? 74 ? 41 0f 28 c2 // 1.20.3X+.
f6 83 ? ? ? ? ? 74 ? 48 8b cb // 1.20.3X+ ?
8b 81 ? ? ? ? d1 e8 a8 ? 48 0f 45 f9 // 1.20.3X+ ?
8b 87 ? ? ? ? d1 e8 a8 ? 0f 84 ? ? ? ? 48 8b 17 // 1.20.3X+ ?
8b 83 ? ? ? ? d1 e8 a8 ? 74 ? 80 bb // 1.20.3X+ ?

f6 87 ? ? ? ? ? 0f 84 ? ? ? ? 4c 8b b7
8b 88 ? ? ? ? 0f 29 b4 24 ? ? ? 0f 28 35

### Level::getRuntimeActorList
48 89 5c 24 18 18 55 56 57 48 83 ec 40 48 8b 05 ? ? ? ? ? ? ? ? 48 33 c4 48 89 44 24 38 48 8b f2 48 8b e9 48 89
xref out and here u go
または40 53 48 83 EC 30 48 81 (1.21.30+)の最初のresをスキャンする

### Level::getPlayerMap
別名 Level::getPlayerList
sigsセクションのメソッドを使用してgetRuntimeActorListを見つける。
第1引数getRuntimeActorListに0xB8を追加する。

### Level::hitResult
// 新しいバージョン用
48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c0 ? 48 83 c4 - 複数の結果が得られるが、最後の1つが正しい。
48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c0 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc 48 8d 81 ? ? ? ? c3 cc cc cc cc cc cc cc cc cc cc cc 40 53
48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc 48 83 ec ? 48 8b 81 ? ? ? ? 48 85 c0 74 ? 48 83 c0 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc 48 8d 81

### GameMode::lastBreakProgress
4d 89 66 ? 49 8b 8e // 1.20.3X+ ?
89 46 ? 80 be

### ScreenView:VisualTree
4c 8b 43 ? 49 8b 08 48 8b 41
48 8b 49 ? 48 8b 01 48 8b 40 ? ? ? ? 84 c0 0f 84 ? ? ? ? 45 32 ff
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ? ? ? 84 c0 74 ? 48 8b 4f ? 83 61 ? ? 48 8b 4f ? 48 8b 01 48 8b 40 ? ff 15 ? ? ? ? 66 0f 1f 84 00
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ? ? ? 84 c0 74 ? 48 8b 4f ? 83 61 ? ? 4c 8b 87
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ? ? ? 84 c0 74 ? 48 8b 4f ? 83 61 ? ? 48 8b 4f ? 48 8b 01 48 8b 40 ? ff 15 ? ? ? ? 48 8b 4f
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ? ? ? 84 c0 74 ? 48 8b b7
4c 8b 47 ? 49 8b 08 48 8b 41 ?
48 8b 4f ? 48 8b 01 ba ? ? ? ? 48 8b 40 ? ? ? ? 84 c0 75 ? 48 8b 4f ? 48 8b 41 ? 48 39 41 ? 75 ? 48 8b 81 ? ? ? ? 48 39 81 ? ? ? ? 75 ? 48 8b 81 ? ? ? ? 48 39 81 ? ? ? ? 75 ? 80 b9

# Sigs to functions

### ItemRenderer::renderGuiItemNew
textures/entity/shulker/shulker_
xrefを1回出力し、最後のfuncにxrefを出力すると、次のようになる。

### HudCursorRenderer::render
「textures/ui/cross_hair」または「ui_crosshair」をStringとして探します。

### ItemRenderer::render
この番号 「0x80100240C00」 を探します。

### HudMobEffectsRenderer::render 
「textures/ui/hud_mob_effect_background」をStringとして探します。