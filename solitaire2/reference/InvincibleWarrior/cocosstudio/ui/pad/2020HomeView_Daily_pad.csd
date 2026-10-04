<GameFile>
  <PropertyGroup Name="2020HomeView_Daily_pad" Type="Layer" ID="c6283b2f-74e9-4ba2-835f-83276e596ed8" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="70" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="-725500090" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="30" Tween="False" Value="255" />
          <IntFrame FrameIndex="60" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="70" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start" StartIndex="35" EndIndex="50">
          <RenderColor A="255" R="238" G="130" B="238" />
        </AnimationInfo>
        <AnimationInfo Name="In" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="75" G="0" B="130" />
        </AnimationInfo>
        <AnimationInfo Name="Out" StartIndex="60" EndIndex="70">
          <RenderColor A="255" R="205" G="133" B="63" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="2" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_root" ActionTag="-725500090" Alpha="0" Tag="7237" IconVisible="False" LeftMargin="-0.0012" RightMargin="0.0012" TopMargin="1.4185" BottomMargin="-1.4185" StretchHeightEnable="True" ClipAble="True" ColorAngle="90.0000" LeftEage="429" RightEage="429" TopEage="633" BottomEage="633" Scale9OriginX="-429" Scale9OriginY="-633" Scale9Width="858" Scale9Height="1266" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Image_44" ActionTag="-1321843388" Alpha="25" Tag="6290" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="195.0000" RightMargin="195.0000" TopMargin="606.4000" BottomMargin="433.6000" Scale9Enable="True" LeftEage="31" RightEage="31" TopEage="24" BottomEage="24" Scale9OriginX="31" Scale9OriginY="24" Scale9Width="5" Scale9Height="2" ctype="ImageViewObjectData">
                <Size X="690.0000" Y="400.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.0000" Y="633.6000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4400" />
                <PreSize X="0.6389" Y="0.2778" />
                <FileData Type="PlistSubImage" Path="ui_homelevel_3.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_57" ActionTag="12220857" Tag="9670" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="362.2000" RightMargin="356.8000" TopMargin="630.6000" BottomMargin="659.4000" TouchEnable="True" FontSize="24" Scale9Enable="True" LeftEage="41" RightEage="41" TopEage="68" BottomEage="74" Scale9OriginX="41" Scale9OriginY="68" Scale9Width="123" Scale9Height="63" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="361.0000" Y="150.0000" />
                <Children>
                  <AbstractNodeData Name="Daiy00_1" ActionTag="971133993" Tag="2720" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="281.5800" RightMargin="36.4200" TopMargin="51.5000" BottomMargin="75.5000" ctype="SpriteObjectData">
                    <Size X="43.0000" Y="23.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="281.5800" Y="87.0000" />
                    <Scale ScaleX="0.7500" ScaleY="0.7500" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7800" Y="0.5800" />
                    <PreSize X="0.1191" Y="0.1533" />
                    <FileData Type="PlistSubImage" Path="Daiy00.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_title_0" ActionTag="-706227899" Tag="5053" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="27.4600" RightMargin="50.5400" TopMargin="25.5000" BottomMargin="49.5000" IsCustomSize="True" FontSize="54" LabelText="2020.3月" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="283.0000" Y="75.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="310.4600" Y="87.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8600" Y="0.5800" />
                    <PreSize X="0.7839" Y="0.5000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="542.7000" Y="734.4000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5025" Y="0.5100" />
                <PreSize X="0.3343" Y="0.1042" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Particle_2" ActionTag="1518650642" Tag="129" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="547.4520" RightMargin="532.5480" TopMargin="557.5680" BottomMargin="882.4320" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="547.4520" Y="882.4320" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5069" Y="0.6128" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/daily0.plist" Plist="" />
                <BlendFunc Src="1" Dst="1" />
              </AbstractNodeData>
              <AbstractNodeData Name="Particle_4" ActionTag="542205570" Tag="131" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="547.4520" RightMargin="532.5480" TopMargin="557.5680" BottomMargin="882.4320" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="547.4520" Y="882.4320" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5069" Y="0.6128" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/daily1.plist" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="FileNode_trophy" ActionTag="-915063137" Tag="204" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="619.2000" BottomMargin="820.8000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="540.0000" Y="820.8000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5700" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="ui/2020Daily_Trophy.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="FileNode_crown" ActionTag="1856742747" Tag="223" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="590.4000" BottomMargin="849.6000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="540.0000" Y="849.6000" />
                <Scale ScaleX="0.7000" ScaleY="0.7000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5900" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="ui/2020Daily_Crown.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_diamondBG" ActionTag="246418176" VisibleForFrame="False" Tag="427" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-619.9000" RightMargin="1415.9000" TopMargin="446.0480" BottomMargin="937.9520" Scale9Enable="True" LeftEage="34" RightEage="34" TopEage="30" BottomEage="30" Scale9OriginX="34" Scale9OriginY="30" Scale9Width="48" Scale9Height="40" ctype="ImageViewObjectData">
                <Size X="284.0000" Y="56.0000" />
                <Children>
                  <AbstractNodeData Name="ui_Crown_0_3" ActionTag="595886615" Tag="421" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="50.2436" RightMargin="187.7564" TopMargin="5.0000" BottomMargin="5.0000" ctype="SpriteObjectData">
                    <Size X="46.0000" Y="46.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="73.2436" Y="28.0000" />
                    <Scale ScaleX="0.6600" ScaleY="0.6400" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2579" Y="0.5000" />
                    <PreSize X="0.1620" Y="0.8214" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_diamond" ActionTag="-1718005766" Tag="422" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="113.6000" RightMargin="85.4000" TopMargin="7.5600" BottomMargin="6.4400" FontSize="36" LabelText="X100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="85.0000" Y="42.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="113.6000" Y="27.4400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4000" Y="0.4900" />
                    <PreSize X="0.2993" Y="0.7500" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-477.9000" Y="965.9520" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.4425" Y="0.6708" />
                <PreSize X="0.2630" Y="0.0389" />
                <FileData Type="PlistSubImage" Path="game_score0.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_2" ActionTag="-1867099155" Tag="7241" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="541.0800" RightMargin="538.9200" TopMargin="847.1520" BottomMargin="592.8480" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Button_hardRight" ActionTag="1506027629" Tag="7253" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="370.0000" RightMargin="-430.0000" TopMargin="-73.4669" BottomMargin="-73.4669" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" Scale9OriginX="15" Scale9Width="30" Scale9Height="88" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="60.0000" Y="146.9337" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="370.0000" />
                    <Scale ScaleX="1.3000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="ui_btn_2.png" Plist="ui.plist" />
                    <PressedFileData Type="PlistSubImage" Path="ui_btn_1.png" Plist="ui.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_btn_0.png" Plist="ui.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_hardLeft1" ActionTag="1621193063" Tag="7254" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-370.0000" RightMargin="310.0000" TopMargin="-79.6704" BottomMargin="-79.6704" TouchEnable="True" FlipX="True" FontSize="14" LeftEage="15" RightEage="15" Scale9OriginX="15" Scale9Width="30" Scale9Height="88" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="60.0000" Y="159.3409" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="-370.0000" />
                    <Scale ScaleX="1.3000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="ui_btn_2.png" Plist="ui.plist" />
                    <PressedFileData Type="PlistSubImage" Path="ui_btn_1.png" Plist="ui.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_btn_0.png" Plist="ui.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_5" ActionTag="-591472281" Tag="7247" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-302.0000" RightMargin="-302.0000" TopMargin="-85.0000" BottomMargin="-85.0000" Scale9Enable="True" LeftEage="52" RightEage="52" TopEage="52" BottomEage="52" Scale9OriginX="52" Scale9OriginY="52" Scale9Width="24" Scale9Height="24" ctype="ImageViewObjectData">
                    <Size X="604.0000" Y="170.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.1800" ScaleY="1.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Challenge_chuangkoubg3.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="PageView_1" ActionTag="1472345679" Tag="2942" IconVisible="False" LeftMargin="-340.0000" RightMargin="-340.0000" TopMargin="-94.0000" BottomMargin="-94.0000" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" ctype="PageViewObjectData">
                    <Size X="680.0000" Y="188.0000" />
                    <AnchorPoint />
                    <Position X="-340.0000" Y="-94.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <SingleColor A="255" R="150" G="150" B="100" />
                    <FirstColor A="255" R="150" G="150" B="100" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="541.0800" Y="592.8480" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5010" Y="0.4117" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Panel_item" ActionTag="-2090682729" Tag="2943" IconVisible="False" LeftMargin="-956.2500" RightMargin="1356.2500" TopMargin="472.2864" BottomMargin="779.7136" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="680.0000" Y="188.0000" />
                <AnchorPoint />
                <Position X="-956.2500" Y="779.7136" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.8854" Y="0.5415" />
                <PreSize X="0.6296" Y="0.1306" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_1" ActionTag="1159762770" Tag="3873" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="202.3760" RightMargin="197.6240" TopMargin="938.0155" BottomMargin="261.9365" StretchHeightEnable="True" Scale9Enable="True" LeftEage="60" RightEage="60" TopEage="48" BottomEage="6" Scale9OriginX="60" Scale9OriginY="48" Scale9Width="62" Scale9Height="94" ctype="ImageViewObjectData">
                <Size X="680.0000" Y="240.0480" />
                <Children>
                  <AbstractNodeData Name="Button_start" ActionTag="2035210927" Tag="3874" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="90.0000" RightMargin="90.0000" TopMargin="23.1406" BottomMargin="63.5647" TouchEnable="True" StretchHeightEnable="True" FontSize="14" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="43" BottomEage="49" Scale9OriginX="90" Scale9OriginY="43" Scale9Width="91" Scale9Height="30" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="153.3427" />
                    <Children>
                      <AbstractNodeData Name="Text_start" ActionTag="-223752227" Tag="3875" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="154.0000" RightMargin="154.0000" TopMargin="41.1379" BottomMargin="44.2048" FontSize="60" LabelText="START" ShadowOffsetX="0.0000" ShadowOffsetY="-4.0000" ctype="TextObjectData">
                        <Size X="192.0000" Y="68.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="250.0000" Y="78.2048" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5100" />
                        <PreSize X="0.3840" Y="0.4435" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="0" G="0" B="0" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="340.0000" Y="140.2360" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5842" />
                    <PreSize X="0.7353" Y="0.6388" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_yellow2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_yellow1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_yellow0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="542.3760" Y="381.9605" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5022" Y="0.2653" />
                <PreSize X="0.6296" Y="0.1667" />
                <FileData Type="PlistSubImage" Path="Ui_Preview3.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_toDay" ActionTag="1908747407" Tag="5045" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="270.0000" RightMargin="640.0000" TopMargin="630.6000" BottomMargin="659.4000" TouchEnable="True" FontSize="24" Scale9Enable="True" LeftEage="41" RightEage="41" TopEage="68" BottomEage="74" Scale9OriginX="41" Scale9OriginY="68" Scale9Width="123" Scale9Height="63" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="170.0000" Y="150.0000" />
                <Children>
                  <AbstractNodeData Name="Node_3" ActionTag="1566403492" Tag="5046" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="85.0000" RightMargin="85.0000" TopMargin="63.0000" BottomMargin="87.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_ti1" ActionTag="-1739761180" Tag="5049" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-54.0000" RightMargin="-54.0000" TopMargin="-30.5000" BottomMargin="-30.5000" FontSize="54" LabelText="今天" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="108.0000" Y="61.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="85.0000" Y="87.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5800" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position X="270.0000" Y="734.4000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2500" Y="0.5100" />
                <PreSize X="0.1574" Y="0.1042" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_57_0_0" Visible="False" ActionTag="73472085" VisibleForFrame="False" Tag="5331" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="687.3120" RightMargin="222.6880" TopMargin="621.6720" BottomMargin="668.3280" TouchEnable="True" FontSize="24" Scale9Enable="True" LeftEage="41" RightEage="41" TopEage="68" BottomEage="74" Scale9OriginX="41" Scale9OriginY="68" Scale9Width="123" Scale9Height="63" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="170.0000" Y="150.0000" />
                <Children>
                  <AbstractNodeData Name="Node_3" ActionTag="2136816509" Tag="5332" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="85.0000" RightMargin="85.0000" TopMargin="63.0000" BottomMargin="87.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_title11" ActionTag="-47549997" Tag="5333" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-73.5000" RightMargin="-73.5000" TopMargin="-37.5000" BottomMargin="-37.5000" IsCustomSize="True" FontSize="54" LabelText="今天" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="147.0000" Y="75.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="85.0000" Y="87.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5800" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position X="687.3120" Y="743.3280" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6364" Y="0.5162" />
                <PreSize X="0.1574" Y="0.1042" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_help" ActionTag="896564244" Tag="204" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="649.0720" RightMargin="260.9280" TopMargin="630.6000" BottomMargin="659.4000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="57" RightEage="57" TopEage="55" BottomEage="82" Scale9OriginX="57" Scale9OriginY="55" Scale9Width="91" Scale9Height="68" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="170.0000" Y="150.0000" />
                <Children>
                  <AbstractNodeData Name="Node_2_0" ActionTag="2055226096" Tag="5334" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="88.4000" RightMargin="81.6000" TopMargin="112.5000" BottomMargin="37.5000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="daily_icon0_1" ActionTag="1757861365" Tag="4032" IconVisible="False" LeftMargin="-36.0000" RightMargin="-36.0000" TopMargin="-107.0000" BottomMargin="31.0000" ctype="SpriteObjectData">
                        <Size X="72.0000" Y="76.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_total1_0" ActionTag="-728310274" Tag="4033" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="23.0000" RightMargin="23.0000" TopMargin="16.5600" BottomMargin="7.4400" FontSize="45" LabelText="1" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="26.0000" Y="52.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="36.0000" Y="33.4400" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="28" G="28" B="28" />
                            <PrePosition X="0.5000" Y="0.4400" />
                            <PreSize X="0.3611" Y="0.6842" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="69.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="Ui_daily0.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_total1" ActionTag="-1573427580" Tag="5337" IconVisible="False" LeftMargin="-72.8338" RightMargin="15.0002" TopMargin="-49.5285" BottomMargin="-3.4715" IsCustomSize="True" FontSize="46" LabelText="1" HorizontalAlignmentType="HT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="57.8336" Y="53.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="-15.0002" Y="23.0285" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_total2_1" ActionTag="995150103" Tag="5338" IconVisible="False" LeftMargin="-17.0000" RightMargin="4.0000" TopMargin="-49.5285" BottomMargin="-3.4715" FontSize="46" LabelText="/" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="13.0000" Y="53.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="-4.0000" Y="23.0285" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="57" G="206" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_total2" ActionTag="-1100165395" Tag="5339" IconVisible="False" LeftMargin="3.0001" RightMargin="-55.0001" TopMargin="-49.5290" BottomMargin="-3.4710" FontSize="46" LabelText="31" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="52.0000" Y="53.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="3.0001" Y="23.0290" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="57" G="206" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="88.4000" Y="37.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5200" Y="0.2500" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="819.0720" Y="734.4000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7584" Y="0.5100" />
                <PreSize X="0.1574" Y="0.1042" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="539.9988" Y="1438.5815" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.9990" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="53" G="83" B="115" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>