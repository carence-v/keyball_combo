# Keyball Series

![Keyball61](./keyball61/doc/rev1/images/kb61_001.jpg)

Keyball series is keyboard family which have 100% track ball.

Keyboards in the family are:

* Available
    * Keyball39: split + 39 keys + a track ball
    * Keyball44: split + 44 keys + a track ball
    * Keyball61: split + 61 keys + a track ball
* Unavailable
    * Keyball46 (first one!)
    * One47

## Where to Buy

|Keyboard   |Shirogane Lab / 白銀ラボ                                   |Yushakobo / 遊舎工房                       |
|-----------|-------------------------------------------|-----------------------------------------------------------|
|Keyball39  |<https://shiroganelab.com/products/keyball39> |<https://shop.yushakobo.jp/products/5357>  |
|Keyball44  |<https://shiroganelab.com/products/keyball44> |<https://shop.yushakobo.jp/products/8337>  |
|Keyball61  |<https://shiroganelab.com/products/keyball61> |<https://shop.yushakobo.jp/products/5358>  |

## Build Guide

*   Keyball39:
    [English/英語](/keyball39/doc/rev1/buildguide_en.md),
    [日本語/Japanese](./keyball39/doc/rev1/buildguide_jp.md)
*   Keyball44:
    [English/英語](./keyball44/doc/rev1/buildguide_en.md),
    [日本語/Japanese](./keyball44/doc/rev1/buildguide_jp.md)
*   Keyball61:
    [English/英語](./keyball61/doc/rev1/buildguide_en.md),
    [日本語/Japanese](./keyball61/doc/rev1/buildguide_jp.md)

## Firmware

See [document for firmware source code](./qmk_firmware/keyboards/keyball/readme.md).

### Pre-compiled Firmwares

(TO BE DOCUMENTED)

---

## carence 専用カスタム仕様

当リポジトリでは、オリジナル（Yowkees氏）のファームウェアをベースに、以下のような専用のキーマップ設定・ライブラリの拡張・ビルドサイズ軽量化を施しています。

### 1. `carence` キーマッププロファイル
専用のキーマッププロファイルとして `qmk_firmware/keyboards/keyball/keyball44/keymaps/carence/` を作成し、カスタマイズを行っています。

#### レイヤー定義とLEDカラー
レイヤーの切り替えに応じて、キーボードのLED（アンダーグロウ）の色が自動的に単色で切り替わります（容量削減のため、アニメーション・エフェクトは無効化）。

実装参考: https://note.com/yinouet1001/n/na3b132c060f3

*   **レイヤー 0 (基本レイヤー)**: `Spring Green`
*   **レイヤー 1 (関数/マウスキー)**: `Red`
*   **レイヤー 2 (数値/記号キー)**: `Azure`
*   **レイヤー 3 (RGB/QMK機能/スクロール用)**: `Magenta` (このレイヤーが有効な間は、スクロールモードが自動的にONになります)
*   **レイヤー 4 (予備レイヤー)**: `White`

#### JIS配列用 同時押しコンボ（17種類）
主に基本レイヤー（レイヤー0）において、2キー同時押しで記号や特定の操作をすばやく入力できます。JIS配列環境での変換に対応したキーコードを出力します。

US配列キーボードからJIS-OSに接続する時の参考文献
https://zenn.dev/yoichi/articles/keymap-that-allow-recovery-from-layout-mismatch
https://www.minagi.jp/2020/09/10/keyboardlayout_jis_us/
https://qiita.com/TKR/items/c9bd6bfd564fa5bf1231

コンボキー自体の実装参考
https://note.com/mamelog0103/n/n5a51fcd24f26

| 同時押しキー | 出力内容 (JIS) | 説明 |
| :--- | :--- | :--- |
| `J` + `Q` | `?` | 疑問符 |
| `J` + `S` | `'` | シングルクォーテーション (`&` キーコード出力) |
| `J` + `W` | `"` | ダブルクォーテーション (`@` キーコード出力) |
| `J` + `B` | `\|` | 縦棒 (`Shift + ￥` キーコード出力) |
| `F` + `P` | `%` | パーセント |
| `J` + `D` | `$` | ドル記号 |
| `F` + `U` | `_` | アンダースコア (`Shift + ろ` キーコード出力) |
| `J` + `A` | `&` | アンパサンド (`^` キーコード出力) |
| `F` + `H` | `#` | ハッシュ記号 |
| `J` + `E` | `!` | 感嘆符 |
| `F` + `N` | `~` | チルダ (`Shift + ^` キーコード出力) |
| `F` + `Y` | `^` | キャレット (`テンキーの=` キーコード出力) |
| `Q` + `W` | `ESC` | エスケープコマンド |
| `J` + `F` | `Caps Word` | 大文字単語入力（Caps Wordトグル） |
| `U` + `I` | `↑` | カーソル上移動 |
| `M` + `,` | `↓` | カーソル下移動 |
| `J` + `K` | `←` | カーソル左移動 |
| `K` + `L` | `→` | カーソル右移動 |

---

### 2. オートマウス機能の拡張（共通ライブラリの変更）
QMK標準の `POINTING_DEVICE_AUTO_MOUSE_ENABLE` を有効化し、トラックボールを動かした際に自動的にマウスレイヤー（レイヤー1）へ移行する設定を行っています。これに伴い、共通ライブラリを拡張しました。

文字入力の際は最初に英数かかなのキーを入力する運用を想定して組んでいる、


*   **タイムアウト上限時間の拡張**: 
    `keyball.c` におけるタイムアウト時間の最大上限（`AML_TIMEOUT_MAX`）を `1000ms`（1秒）から **`65535ms`**（約65秒）に拡張し、長い待機時間を設定できるようにしました（`AUTO_MOUSE_TIME` は `10000ms` に設定）。
*   **変動量子化単位の調整**:
    タイムアウト時間をキーで増減する単位（`AML_TIMEOUT_QU`）を `50ms` から **`500ms`** に変更しました。
*   **OLEDディスプレイ表示の改善**:
    5桁のミリ秒を画面幅制限（横21文字）に収めて表示崩れを防ぐため、OLED上では **秒単位（` 1s`〜`65s`、切り捨て）** で表示するように修正しました。

---

### 3. フラッシュメモリ容量の徹底削減（最適化）
Pro Micro（AVRマイコン）の容量制限（28KB）をクリアするため、以下の最適化設定を適用しています。

軽量化参考
https://zenn.dev/koron/articles/98324ab760e83a

#### `rules.mk`
*   `LTO_ENABLE = yes` (リンクタイムオプティマイズの有効化、大幅な削減効果)
*   `MUSIC_ENABLE = no` (音楽機能無効化)
*   `SPACE_CADET_ENABLE = no` (Space Cadet修飾キー無効化)
*   `GRAVE_ESC_ENABLE = no` (Grave Escape機能無効化)
*   `MAGIC_ENABLE = no` (マジックキーコード機能無効化)
*   `EXTRAKEY_ENABLE = no` (システムコントロール/オーディオキー無効化)
*   `COMMAND_ENABLE = no` (デバッグコマンド無効化)

#### `config.h`
*   `#define NO_DEBUG` (デバッグ機能の除外)
*   `#define NO_PRINT` (プリントデバッグ機能の除外)
*   `#define NO_ACTION_ONESHOT` (ワンショットキー機能の除外)
*   `#define NO_ACTION_MACRO` (古いマクロ機能の除外)
*   `#define NO_ACTION_FUNCTION` (古いファンクションキー機能の除外)
*   `#define LAYER_STATE_8BIT` (レイヤー状態のデータ幅を8ビットに縮小)
*   `#undef LOCKING_SUPPORT_ENABLE` / `#undef LOCKING_RESYNC_ENABLE` (ロックキーサポートの除外)

