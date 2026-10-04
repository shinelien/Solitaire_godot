<GameFile>
  <PropertyGroup Name="NewShop" Type="Layer" ID="55f1abb3-b5c7-4250-aa6e-f0f571bdc765" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="200" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="294280812" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="15" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-210907619" Property="Alpha">
          <IntFrame FrameIndex="6" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="12" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="88100711" Property="Position">
          <PointFrame FrameIndex="25" X="-333.3331" Y="546.6626">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="199580910" Property="Position">
          <PointFrame FrameIndex="0" X="540.0000" Y="480.7264">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="540.0000" Y="814.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1315137066" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="11" />
          </IntFrame>
          <IntFrame FrameIndex="10" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="962201887" Property="Alpha">
          <IntFrame FrameIndex="190" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="200" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="962201887" Property="Position">
          <PointFrame FrameIndex="190" X="540.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="200" X="540.0000" Y="-500.0000">
            <EasingData Type="26" />
          </PointFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="105" G="105" B="105" />
        </AnimationInfo>
        <AnimationInfo Name="out" StartIndex="60" EndIndex="100">
          <RenderColor A="255" R="147" G="112" B="219" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="78" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="294280812" Tag="374" IconVisible="False" LeftMargin="0.0006" RightMargin="-0.0006" TopMargin="-781.1208" BottomMargin="-298.8792" TouchEnable="True" ClipAble="False" BackColorAlpha="114" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="3000.0000" />
            <AnchorPoint />
            <Position X="0.0006" Y="-298.8792" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="-0.1557" />
            <PreSize X="1.0000" Y="1.5625" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_shop" ActionTag="-1315137066" Tag="23" IconVisible="False" PositionPercentXEnabled="True" VerticalEdge="BottomEdge" TopMargin="-5.2804" BottomMargin="5.2804" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Panel_out" ActionTag="-1664370828" Tag="478" IconVisible="False" LeftMargin="22.5171" RightMargin="21.7096" TopMargin="470.8538" BottomMargin="156.6931" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1035.7733" Y="1292.4531" />
                <AnchorPoint />
                <Position X="22.5171" Y="156.6931" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0208" Y="0.0816" />
                <PreSize X="0.9590" Y="0.6732" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="game0_uibg1_9_1" ActionTag="1676797928" Tag="484" IconVisible="False" PositionPercentXEnabled="True" RightMargin="992.0000" TopMargin="-324.0012" BottomMargin="2128.0012" ctype="SpriteObjectData">
                <Size X="88.0000" Y="116.0000" />
                <AnchorPoint ScaleY="1.0000" />
                <Position Y="2244.0012" />
                <Scale ScaleX="12.2867" ScaleY="6.9704" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="1.1688" />
                <PreSize X="0.0815" Y="0.0604" />
                <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_2" ActionTag="199580910" Tag="404" IconVisible="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="1106.0000" BottomMargin="814.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_11" ActionTag="-210907619" Tag="449" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-572.7228" RightMargin="-572.7228" TopMargin="-566.5691" BottomMargin="-771.3114" Scale9Enable="True" LeftEage="97" RightEage="97" TopEage="133" BottomEage="133" Scale9OriginX="97" Scale9OriginY="133" Scale9Width="102" Scale9Height="139" ctype="ImageViewObjectData">
                    <Size X="1145.4456" Y="1337.8805" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="566.5691" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="main_table1.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_detail2_15" ActionTag="-722402238" Tag="406" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-125.0000" RightMargin="-125.0000" TopMargin="-654.5000" BottomMargin="613.5000" ctype="SpriteObjectData">
                    <Size X="250.0000" Y="41.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="634.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_detail2.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_detail2_15_0" ActionTag="-2018235678" Tag="407" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-125.0000" RightMargin="-125.0000" TopMargin="-654.5000" BottomMargin="613.5000" ctype="SpriteObjectData">
                    <Size X="250.0000" Y="41.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="634.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_detail2.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_1" ActionTag="-1762025381" Tag="408" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-504.0000" TopMargin="-609.9985" BottomMargin="-642.0015" LeftEage="153" RightEage="153" TopEage="389" BottomEage="389" Scale9OriginX="153" Scale9OriginY="389" Scale9Width="159" Scale9Height="402" ctype="ImageViewObjectData">
                    <Size X="504.0000" Y="1252.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_1_0" ActionTag="1897940054" Tag="409" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" FlipX="True" LeftEage="153" RightEage="153" TopEage="389" BottomEage="389" Scale9OriginX="153" Scale9OriginY="389" Scale9Width="159" Scale9Height="402" ctype="ImageViewObjectData">
                        <Size X="504.0000" Y="1252.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="504.0000" Y="626.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position Y="609.9985" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9_1" Visible="False" ActionTag="674838967" VisibleForFrame="False" Tag="410" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-44.0000" RightMargin="-44.0000" TopMargin="441.0002" BottomMargin="-557.0002" FlipY="True" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="0.5000" />
                    <Position Y="-557.0002" />
                    <Scale ScaleX="10.5531" ScaleY="0.5575" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="ListView_bg" ActionTag="-219074175" Tag="1548" IconVisible="False" LeftMargin="-496.5000" RightMargin="-496.5000" TopMargin="-453.0003" BottomMargin="-507.3328" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" IsBounceEnabled="True" ScrollDirectionType="0" DirectionType="Vertical" ctype="ListViewObjectData">
                    <Size X="993.0000" Y="960.3331" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="453.0003" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <SingleColor A="255" R="150" G="150" B="255" />
                    <FirstColor A="255" R="150" G="150" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9" ActionTag="767264961" Tag="412" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-44.0000" RightMargin="-44.0000" TopMargin="-476.0000" BottomMargin="360.0000" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="418.0000" />
                    <Scale ScaleX="11.3844" ScaleY="0.6955" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9_0" ActionTag="1174245578" Tag="413" RotationSkewX="-90.0000" RotationSkewY="-90.0002" IconVisible="False" LeftMargin="422.9967" RightMargin="-510.9967" TopMargin="-723.0001" BottomMargin="607.0001" FlipY="True" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="1.0000" />
                    <Position X="510.9967" Y="607.0001" />
                    <Scale ScaleX="14.0705" ScaleY="0.4700" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9_0_0" ActionTag="-1076568179" Tag="414" RotationSkewX="-90.0000" RotationSkewY="-90.0002" IconVisible="False" LeftMargin="-591.9996" RightMargin="503.9996" TopMargin="-606.9998" BottomMargin="490.9998" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position X="-503.9996" Y="606.9998" />
                    <Scale ScaleX="14.1192" ScaleY="0.4700" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg2_3_0" ActionTag="2037062734" Tag="415" IconVisible="False" LeftMargin="502.9993" RightMargin="-517.9993" TopMargin="-624.7778" BottomMargin="-831.2222" FlipX="True" ctype="SpriteObjectData">
                    <Size X="15.0000" Y="1456.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position X="517.9993" Y="624.7778" />
                    <Scale ScaleX="1.0000" ScaleY="0.8781" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg2_3" ActionTag="-884211945" Tag="416" IconVisible="False" LeftMargin="-516.9982" RightMargin="501.9982" TopMargin="-624.7740" BottomMargin="-831.2260" ctype="SpriteObjectData">
                    <Size X="15.0000" Y="1456.0000" />
                    <AnchorPoint ScaleY="1.0000" />
                    <Position X="-516.9982" Y="624.7740" />
                    <Scale ScaleX="1.0000" ScaleY="0.8793" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2_1_0_0_0" ActionTag="-269013680" Tag="649" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-517.2944" RightMargin="-517.2944" TopMargin="-624.7800" BottomMargin="608.7800" Scale9Enable="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="315" Scale9OriginY="5" Scale9Width="327" Scale9Height="6" ctype="ImageViewObjectData">
                    <Size X="1034.5889" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="616.7800" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2_0" ActionTag="1426564668" Tag="428" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-517.0000" RightMargin="-517.0000" TopMargin="639.0000" BottomMargin="-655.0000" FlipY="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="315" Scale9OriginY="5" Scale9Width="327" Scale9Height="6" ctype="ImageViewObjectData">
                    <Size X="1034.0000" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-647.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg9_1" ActionTag="-826452025" Tag="648" IconVisible="False" LeftMargin="-506.6660" RightMargin="-445.3340" TopMargin="-611.3341" BottomMargin="478.3341" ctype="SpriteObjectData">
                    <Size X="952.0000" Y="133.0000" />
                    <AnchorPoint ScaleY="1.0000" />
                    <Position X="-506.6660" Y="611.3341" />
                    <Scale ScaleX="1.0693" ScaleY="1.1003" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_tab3" ActionTag="-43368572" Tag="1" IconVisible="False" LeftMargin="-498.0000" RightMargin="166.0000" TopMargin="503.0000" BottomMargin="-633.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="140" RightEage="125" TopEage="50" BottomEage="39" Scale9OriginX="140" Scale9OriginY="50" Scale9Width="40" Scale9Height="57" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="332.0000" Y="130.0000" />
                    <Children>
                      <AbstractNodeData Name="text_title1" ActionTag="-1157570446" Alpha="178" Tag="31" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="86.0000" RightMargin="86.0000" TopMargin="67.2000" BottomMargin="17.8000" FontSize="40" LabelText="纸牌背面" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="166.0000" Y="40.3000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="82" G="55" B="4" />
                        <PrePosition X="0.5000" Y="0.3100" />
                        <PreSize X="0.4819" Y="0.3462" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="storecard_1_2" ActionTag="319995000" Tag="954" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="142.0000" RightMargin="142.0000" TopMargin="18.3000" BottomMargin="67.7000" ctype="SpriteObjectData">
                        <Size X="48.0000" Y="44.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="166.0000" Y="89.7000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.6900" />
                        <PreSize X="0.1446" Y="0.3385" />
                        <FileData Type="PlistSubImage" Path="storecard_1.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="-166.0000" Y="-568.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_store_btn3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_store_btn2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_tab2" ActionTag="180524406" Tag="2" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-166.0000" RightMargin="-166.0000" TopMargin="503.0000" BottomMargin="-633.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="275" Scale9Height="124" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="332.0000" Y="130.0000" />
                    <Children>
                      <AbstractNodeData Name="storecard_2_3" ActionTag="1508586547" Tag="955" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="134.5000" RightMargin="134.5000" TopMargin="9.8000" BottomMargin="59.2000" ctype="SpriteObjectData">
                        <Size X="63.0000" Y="61.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="166.0000" Y="89.7000" />
                        <Scale ScaleX="0.8500" ScaleY="0.8500" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.6900" />
                        <PreSize X="0.1898" Y="0.4692" />
                        <FileData Type="PlistSubImage" Path="storecard_2.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_title2" ActionTag="-39965726" Alpha="178" Tag="29" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="86.0000" RightMargin="86.0000" TopMargin="67.2000" BottomMargin="17.8000" FontSize="40" LabelText="纸牌正面" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="166.0000" Y="40.3000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="60" G="39" B="0" />
                        <PrePosition X="0.5000" Y="0.3100" />
                        <PreSize X="0.4819" Y="0.3462" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-568.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_store_btn3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_store_btn2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_tab1" ActionTag="1001682534" Alpha="249" Tag="3" IconVisible="False" LeftMargin="166.0000" RightMargin="-498.0000" TopMargin="502.7140" BottomMargin="-632.7140" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="275" Scale9Height="124" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="332.0000" Y="130.0000" />
                    <Children>
                      <AbstractNodeData Name="storecard_0_1" ActionTag="1516402342" Tag="953" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="134.5000" RightMargin="134.5000" TopMargin="8.4480" BottomMargin="60.5520" ctype="SpriteObjectData">
                        <Size X="63.0000" Y="61.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="166.0000" Y="91.0520" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.7004" />
                        <PreSize X="0.1898" Y="0.4692" />
                        <FileData Type="PlistSubImage" Path="storecard_0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_title3" ActionTag="437520541" Alpha="178" Tag="27" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="86.0000" RightMargin="86.0000" TopMargin="67.2000" BottomMargin="17.8000" FontSize="40" LabelText="游戏背景" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="166.0000" Y="40.3000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="60" G="39" B="0" />
                        <PrePosition X="0.5000" Y="0.3100" />
                        <PreSize X="0.4819" Y="0.3462" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.4978" />
                    <Position X="166.0000" Y="-568.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_store_btn3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_store_btn2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2_1_0_0" ActionTag="-1540358638" Tag="785" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-517.2944" RightMargin="-517.2944" TopMargin="-470.1100" BottomMargin="454.1100" Scale9Enable="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="315" Scale9OriginY="5" Scale9Width="327" Scale9Height="6" ctype="ImageViewObjectData">
                    <Size X="1034.5889" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="462.1100" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_shop_close" ActionTag="1021498041" Tag="429" IconVisible="False" LeftMargin="446.5770" RightMargin="-566.5770" TopMargin="-692.0490" BottomMargin="572.0490" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="90" Scale9Height="98" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="120.0000" Y="120.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="506.5770" Y="632.0490" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_btn_close3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_btn_close2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="img_btn_coin" ActionTag="88100711" Tag="421" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="-484.9221" RightMargin="181.7442" TopMargin="-572.2162" BottomMargin="521.1089" TouchEnable="True" Scale9Enable="True" LeftEage="24" RightEage="24" TopEage="30" BottomEage="30" Scale9OriginX="24" Scale9OriginY="30" Scale9Width="4" Scale9Height="1" ctype="ImageViewObjectData">
                    <Size X="303.1779" Y="51.1073" />
                    <Children>
                      <AbstractNodeData Name="img_icon0_1" ActionTag="-1935565214" Tag="216" IconVisible="False" LeftMargin="-25.4793" RightMargin="183.6572" TopMargin="-48.2679" BottomMargin="-42.6248" ctype="SpriteObjectData">
                        <Size X="145.0000" Y="142.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="47.0207" Y="28.3752" />
                        <Scale ScaleX="0.4000" ScaleY="0.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1551" Y="0.5552" />
                        <PreSize X="0.4783" Y="2.7785" />
                        <FileData Type="PlistSubImage" Path="img_icon0.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="atlasLabel_coin" ActionTag="197760475" VisibleForFrame="False" Tag="423" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-359.7945" RightMargin="592.9724" TopMargin="36.0153" BottomMargin="-2.9080" CharWidth="14" CharHeight="18" LabelText="20000" StartChar="." ctype="TextAtlasObjectData">
                        <Size X="70.0000" Y="18.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-324.7945" Y="6.0920" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="-1.0713" Y="0.1192" />
                        <PreSize X="0.2309" Y="0.3522" />
                        <LabelAtlasFileImage_CNB Type="Default" Path="Default/TextAtlas.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_3" ActionTag="780280025" Alpha="165" Tag="4408" IconVisible="False" LeftMargin="243.7334" RightMargin="0.6070" TopMargin="0.5881" BottomMargin="-4.9751" Scale9Enable="True" LeftEage="18" RightEage="18" TopEage="18" BottomEage="18" Scale9OriginX="18" Scale9OriginY="18" Scale9Width="20" Scale9Height="20" ctype="ImageViewObjectData">
                        <Size X="58.8375" Y="55.4943" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                        <Position X="302.5709" Y="50.5192" />
                        <Scale ScaleX="0.9000" ScaleY="0.9000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9980" Y="0.9885" />
                        <PreSize X="0.1941" Y="1.0858" />
                        <FileData Type="PlistSubImage" Path="Level_win2.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_add" ActionTag="1012382814" Tag="424" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="250.1041" RightMargin="1.0738" TopMargin="0.9412" BottomMargin="1.1661" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="22" Scale9Height="27" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="52.0000" Y="49.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="276.1041" Y="25.6661" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9107" Y="0.5022" />
                        <PreSize X="0.1715" Y="0.9588" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <NormalFileData Type="Normal" Path="img/img_add.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="BitmapFontLabel_coin" ActionTag="185287474" Tag="425" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="89.8013" RightMargin="-22.6234" TopMargin="-19.3595" BottomMargin="-19.5332" LabelText="3,000" ctype="TextBMFontObjectData">
                        <Size X="236.0000" Y="90.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="89.8013" Y="25.4668" />
                        <Scale ScaleX="0.5500" ScaleY="0.5500" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.2962" Y="0.4983" />
                        <PreSize X="0.7784" Y="1.7610" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_title" ActionTag="-431057936" Tag="32" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="383.1761" RightMargin="-285.9981" TopMargin="-7.4798" BottomMargin="-9.4129" FontSize="60" LabelText="STORE" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="206.0000" Y="68.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="486.1761" Y="24.5871" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="200" B="138" />
                        <PrePosition X="1.6036" Y="0.4811" />
                        <PreSize X="0.6795" Y="1.3305" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="105" G="68" B="27" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-333.3331" Y="546.6626" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_tips.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="814.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4240" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="540.0000" Y="1925.2804" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0028" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="86" G="92" B="124" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_view" ActionTag="-501500674" Tag="1547" IconVisible="False" LeftMargin="-1151.1091" RightMargin="1238.1091" TopMargin="804.5497" BottomMargin="775.4503" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="993.0000" Y="340.0000" />
            <AnchorPoint />
            <Position X="-1151.1091" Y="775.4503" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-1.0658" Y="0.4039" />
            <PreSize X="0.9194" Y="0.1771" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_confirm" Visible="False" ActionTag="1185461547" Tag="2985" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TopMargin="1409.2000" BottomMargin="410.8000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="100.0000" />
            <Children>
              <AbstractNodeData Name="Node_1" ActionTag="962201887" Tag="2986" IconVisible="True" PositionPercentXEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="100.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_40" ActionTag="1066652361" Tag="2987" IconVisible="False" LeftMargin="-469.9998" RightMargin="-470.0002" TopMargin="-300.5000" BottomMargin="-360.5000" LeftEage="60" RightEage="60" TopEage="57" BottomEage="57" Scale9OriginX="60" Scale9OriginY="57" Scale9Width="64" Scale9Height="60" ctype="ImageViewObjectData">
                    <Size X="940.0000" Y="661.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="0.0002" Y="-30.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_challengebg0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_5" ActionTag="-611558911" Tag="2988" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-500.0000" RightMargin="-500.0000" TopMargin="-300.0000" BottomMargin="-300.0000" Scale9Enable="True" LeftEage="42" RightEage="42" TopEage="42" BottomEage="42" Scale9OriginX="42" Scale9OriginY="42" Scale9Width="44" Scale9Height="44" ctype="ImageViewObjectData">
                    <Size X="1000.0000" Y="600.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="39" G="46" B="35" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_6" ActionTag="778901656" Tag="2989" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-483.5000" RightMargin="-483.5000" TopMargin="-285.0000" BottomMargin="-285.0000" Scale9Enable="True" LeftEage="65" RightEage="65" TopEage="65" BottomEage="65" Scale9OriginX="65" Scale9OriginY="65" Scale9Width="14" Scale9Height="14" ctype="ImageViewObjectData">
                    <Size X="967.0000" Y="570.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="61" G="81" B="51" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_4_0" ActionTag="33599380" Tag="3709" IconVisible="False" LeftMargin="-192.4588" RightMargin="-27.5412" TopMargin="-190.0000" BottomMargin="170.0000" Scale9Enable="True" LeftEage="17" RightEage="59" TopEage="6" BottomEage="6" Scale9OriginX="17" Scale9OriginY="6" Scale9Width="12" Scale9Height="8" ctype="ImageViewObjectData">
                    <Size X="220.0000" Y="20.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_4" ActionTag="758160205" Tag="3708" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-440.0000" RightMargin="440.0000" FlipX="True" Scale9Enable="True" LeftEage="17" RightEage="59" TopEage="6" BottomEage="6" Scale9OriginX="17" Scale9OriginY="6" Scale9Width="12" Scale9Height="8" ctype="ImageViewObjectData">
                        <Size X="220.0000" Y="20.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="-220.0000" Y="10.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="ui_storexijie0.png" Plist="ui.plist" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="27.5412" Y="180.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_storexijie0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_dailytips_0" ActionTag="492300432" Tag="3006" IconVisible="False" LeftMargin="-320.0317" RightMargin="70.0317" TopMargin="-101.3879" BottomMargin="44.3879" FontSize="50" LabelText="是否更换？" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="250.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-195.0317" Y="72.8879" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="237" B="144" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_" ActionTag="-1488989896" Tag="3212" IconVisible="False" LeftMargin="-416.0088" RightMargin="36.0088" TopMargin="129.9028" BottomMargin="-259.9028" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="35" RightEage="35" TopEage="11" BottomEage="11" Scale9OriginX="35" Scale9OriginY="11" Scale9Width="201" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="380.0000" Y="130.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_1" ActionTag="-1276852124" Tag="3213" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="140.0000" RightMargin="140.0000" TopMargin="33.9000" BottomMargin="39.1000" FontSize="50" LabelText="返回" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="100.0000" Y="57.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="190.0000" Y="67.6000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5200" />
                        <PreSize X="0.2632" Y="0.4385" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-226.0088" Y="-194.9028" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_" ActionTag="1744499363" Tag="3214" IconVisible="False" LeftMargin="57.2156" RightMargin="-437.2156" TopMargin="128.3873" BottomMargin="-258.3873" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="35" RightEage="35" TopEage="11" BottomEage="11" Scale9OriginX="35" Scale9OriginY="11" Scale9Width="201" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="380.0000" Y="130.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_1" ActionTag="-2100722155" Tag="3215" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="140.0000" RightMargin="140.0000" TopMargin="33.9000" BottomMargin="39.1000" FontSize="50" LabelText="替换" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="100.0000" Y="57.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="190.0000" Y="67.6000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5200" />
                        <PreSize X="0.2632" Y="0.4385" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="247.2156" Y="-193.3873" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button__buy" ActionTag="-1778267151" Tag="3640" IconVisible="False" LeftMargin="57.2156" RightMargin="-437.2156" TopMargin="128.3873" BottomMargin="-258.3873" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="35" RightEage="35" TopEage="11" BottomEage="11" Scale9OriginX="35" Scale9OriginY="11" Scale9Width="201" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="380.0000" Y="130.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_1" ActionTag="-699136684" Tag="3641" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="120.0000" RightMargin="120.0000" TopMargin="33.9000" BottomMargin="39.1000" FontSize="50" LabelText="10000" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="140.0000" Y="57.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="190.0000" Y="67.6000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5200" />
                        <PreSize X="0.3684" Y="0.4385" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="img_icon0_7" ActionTag="-250578853" Tag="3642" IconVisible="False" LeftMargin="6.5511" RightMargin="228.4489" TopMargin="-10.2295" BottomMargin="-1.7705" ctype="SpriteObjectData">
                        <Size X="145.0000" Y="142.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="79.0511" Y="69.2295" />
                        <Scale ScaleX="0.4000" ScaleY="0.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.2080" Y="0.5325" />
                        <PreSize X="0.3816" Y="1.0923" />
                        <FileData Type="PlistSubImage" Path="img_icon0.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="247.2156" Y="-193.3873" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_yellow1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_yellow0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_4_0_0" ActionTag="-435490946" Tag="3710" IconVisible="False" LeftMargin="-192.4589" RightMargin="-27.5411" TopMargin="14.0000" BottomMargin="-34.0000" Scale9Enable="True" LeftEage="17" RightEage="59" TopEage="6" BottomEage="6" Scale9OriginX="17" Scale9OriginY="6" Scale9Width="12" Scale9Height="8" ctype="ImageViewObjectData">
                    <Size X="220.0000" Y="20.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_4" ActionTag="-280102076" Tag="3711" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-440.0000" RightMargin="440.0000" FlipX="True" Scale9Enable="True" LeftEage="17" RightEage="59" TopEage="6" BottomEage="6" Scale9OriginX="17" Scale9OriginY="6" Scale9Width="12" Scale9Height="8" ctype="ImageViewObjectData">
                        <Size X="220.0000" Y="20.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="-220.0000" Y="10.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="ui_storexijie0.png" Plist="ui.plist" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="27.5411" Y="-24.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_storexijie0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_1" ActionTag="-884007267" Tag="3644" RotationSkewX="8.8041" RotationSkewY="8.8016" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="802.6560" RightMargin="277.3440" TopMargin="-15.1600" BottomMargin="115.1600" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="ui_storemodel0_1" ActionTag="-1533129047" Tag="3645" IconVisible="False" LeftMargin="-101.0003" RightMargin="-114.9997" TopMargin="-164.4996" BottomMargin="-144.5004" ctype="SpriteObjectData">
                    <Size X="216.0000" Y="309.0000" />
                    <Children>
                      <AbstractNodeData Name="card_0_1_0_4" ActionTag="-17641751" Tag="3646" RotationSkewX="1.9999" RotationSkewY="2.0003" IconVisible="False" LeftMargin="43.0000" RightMargin="25.0000" TopMargin="20.0000" BottomMargin="69.0000" ctype="SpriteObjectData">
                        <Size X="148.0000" Y="220.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="117.0000" Y="179.0000" />
                        <Scale ScaleX="1.2100" ScaleY="1.2100" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5417" Y="0.5793" />
                        <PreSize X="0.6852" Y="0.7120" />
                        <FileData Type="Normal" Path="card_0_1_0.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="6.9997" Y="9.9996" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_storemodel0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="802.6560" Y="115.1600" />
                <Scale ScaleX="1.3000" ScaleY="1.3000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7432" Y="1.1516" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="460.8000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.2400" />
            <PreSize X="1.0000" Y="0.0521" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>