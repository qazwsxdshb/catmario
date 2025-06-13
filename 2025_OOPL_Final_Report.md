# 2025 OOPL Final Report

# **1.組別資訊**

- 組別：第29組
- 組員：何益森&楊子力
- 復刻遊戲：[Cat Mario](https://catmario.eu/)

# 2.**專案簡介**

- 遊戲簡介

  CatMario是一款惡搞版的橫向捲軸平台遊戲，靈感來自《超級瑪利歐兄弟》。玩家操控一隻可愛的白貓，闖過看似熟悉卻充滿陷阱的關卡。遊戲充滿各種意想不到的機關與挑戰，讓人又氣又笑。雖然難度極高，但正因如此，它深受喜歡挑戰和惡搞風格的玩家喜愛。
- 組別分工

  楊子力：處理素材、製作地圖、放置物件、測試遊戲、報告製作、實作影片

  何益森：角色移動、怪物機制、關卡切換、死亡判定、飛行模式、音效處理

# 3.**遊戲介紹**

- 遊戲規則

  《瑪莉喵》是一款橫向卷軸平台遊戲，玩家需操作主角（白色小貓）從起點移動至關卡終點。過程中設有多種隱藏陷阱與非預期機關，包括會掉落的地板、突然出現的障礙物或敵人等。遊戲未限制死亡次數，鼓勵玩家透過不斷嘗試與記憶來克服關卡挑戰。操作方式以基本的左右移動與跳躍為主，關卡設計強調反直覺與高難度，極具挑戰性與娛樂效果。
- 遊戲畫面

  [起始畫面](https://drive.google.com/file/d/1xsjxYRzPLMwrDw2-Gpv_t_oozBsQmZpq/view?usp=drive_link) 

  [第一關](https://drive.google.com/file/d/1ft5kddby3T0dIO0CUr6seLrnWfWUOMeD/view?usp=drive_link) 

  [轉關一](https://drive.google.com/file/d/1kcFhxsfpEXywQzyAjejeoQrw5HVONq8x/view?usp=drive_link) 

  [第二關](https://drive.google.com/file/d/1LtXhA4upQ4JBbcPxMR1v9YUX_yRYQjFK/view?usp=drive_link) 

  [轉關二](https://drive.google.com/file/d/1dMggl_lIyVgKDsy1kTje4AgEv00zjD5Y/view?usp=drive_link) 

  [第三關](https://drive.google.com/file/d/1ab0Xsxoowhu3B2NPwlLcL5VqjEP-4q4c/view?usp=drive_link) 

  [死亡畫面](https://drive.google.com/file/d/1yydDUfFVPhlIRYpWNKm5oqDFM92LO1dI/view?usp=drive_link) 

# 4.**程式設計**

- 程式架構

  PTSD\include\Util\Renderer.hpp & PTSD\include\Util\BGM.hpp PTSD\include\Util\SFX.hpp -> 遊戲核心(App.hpp)

  PTSD\include\Util\GameObject.hpp & PTSD\include\Util\GameObject.hpp -> 背景文字管理器(BackgroundImage.hpp)

  PTSD\include\Util\GameObject.hpp -> 玩家(Character.hpp)

  PTSD\include\Util\GameObject.hpp -> 金幣(Coin.hpp)

  PTSD\include\Util\GameObject.hpp ->怪物(Monster.hpp)

  PTSD\include\Util\GameObject.hpp -> 方塊(Obstacle.hpp)

  PTSD\include\Util\GameObject.hpp -> 轉關控制(PhaseResourceManger.hpp)

  PTSD\include\Util\GameObject.hpp & PTSD\include\Util\Text.hpp & PTSD\include\Util\Color.hpp ->文字輸出(Textt.hpp)
- 程式技術
  - **遊戲狀態機**：主程式 main.cpp 以 App::State 狀態機控制遊戲流程（如 ZERO、START、UPDATE、DIE、END 等）。
  - **地圖資料驅動**：地圖資料從 CSV 檔載入（如 zerostart.csv），並以二維陣列儲存，對應不同關卡。
  - **物件導向設計**：角色、怪物、障礙物等皆以類別封裝，並有各自的圖片、位置、狀態等屬性。
  - **碰撞偵測**：有多種碰撞判斷函式（如 [Collision]()、[RLCollision]()、[UDCollision]()），用於判斷角色與障礙物、怪物間的互動。
  - **事件與輸入處理**：支援鍵盤輸入（如上下左右、空白鍵、ESC），並根據輸入改變角色狀態或觸發事件。
  - **音效與背景音樂**：支援 BGM 與 SFX 播放（如死亡、跳躍、過關等音效）。
  - **資源管理**：圖片、音效等資源以路徑常數管理，並集中於 [GA_RESOURCE_DIR]() 目錄下。
  - **UI與文字顯示**：有簡單的文字顯示（如提示、分數、過關訊息等）。
  - **地圖與關卡切換**：可根據遊戲進度切換不同地圖與關卡（如一開始是 zerostart，過關後切換到 onestart、twostart 等）。

# 5.**結語**

- 問題與解決方法

  無太大問題
- 自評

  項次 項目 完成

  1 完成協議書上所描述的最小關卡數量 V

  2 完成專案權限改為 public V

  3 具有 debug mode 的功能 V

  4 解決專案上所有 Memory Leak 的問題 V

  5 報告中沒有任何錯字，以及沒有任何一項遺漏 V

  6 報告至少保持基本的美感，人類可讀 V
- 收穫

  這學期讓我們學到了如何用 C++ 開發一款簡單但具有挑戰性的遊戲，我們選擇重現經典的《瑪莉喵》。在製作過程中，我們除了練習基本的角色控制與碰撞偵測，也開始注意到專案結構的安排、程式碼的可讀性，以及怎麼設計出讓玩家「又愛又恨」的關卡。開發過程中當然遇到不少問題，像是角色卡住、陷阱沒反應，或是動畫不順等，但我們一步步找原因、查資料、互相討論，也都順利解決。這次經驗不只讓我們學到技術上的東西，也讓我們更了解遊戲設計的思考方式。最重要的是，這次作品也成為我們作品集裡的一部分，是一個能夠展示我們能力的成果，對我們來說意義很大。未來我們也希望能做出更多更完整、更有趣的遊戲。
- 心得

  這一次開發《瑪莉喵》的過程非常開心，也因為我們前面設計好的基礎架構，在開發遊戲時幫助了我們不少。像是把動畫控制、陷阱觸發等功能模組化，整合進角色與場景系統中，讓整體開發效率提升了不少，也讓我們可以花更多心力在設計細節上。我們也嘗試設計了各種不同的怪物，像是會自動追擊玩家的、碰到就會爆炸的，甚至是假裝是道具的敵人，讓遊戲關卡變得更豐富，也讓玩家每次挑戰都有不同的驚喜與挑戰感。這次專案讓我們更懂得如何安排遊戲邏輯與畫面呈現的結合，也讓我們對遊戲製作的每一個小細節都更有想法。能完成一款能玩的遊戲，並看到自己的設計在畫面中實現，真的非常有成就感。
- 貢獻比例

  何益森 60% 楊子力 40%
