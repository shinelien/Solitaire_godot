<GameFile>
  <PropertyGroup Name="2020Goldbanner" Type="Node" ID="697d358c-663d-4e90-8cd2-c9011ad67419" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="125" Speed="1.0000" ActivedAnimationName="in">
        <Timeline ActionTag="-1564788750" Property="ActionValue">
          <InnerActionFrame FrameIndex="0" Tween="False" InnerActionType="LoopAction" CurrentAniamtionName="Exp" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="-623367365" Property="Position">
          <PointFrame FrameIndex="0" Tween="False" X="101.0000" Y="66.0000" />
          <PointFrame FrameIndex="45" X="30.0000" Y="150.0000">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="52" X="30.0000" Y="150.0000">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="92" Tween="False" X="101.0000" Y="66.0000" />
          <PointFrame FrameIndex="105" X="101.0000" Y="66.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="115" Tween="False" X="30.0000" Y="150.0000" />
          <PointFrame FrameIndex="125" X="75.6000" Y="66.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-623367365" Property="Alpha">
          <IntFrame FrameIndex="0" Tween="False" Value="255" />
          <IntFrame FrameIndex="45" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="52" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="92" Tween="False" Value="255" />
          <IntFrame FrameIndex="105" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="115" Tween="False" Value="0" />
          <IntFrame FrameIndex="125" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="2038003185" Property="ActionValue">
          <InnerActionFrame FrameIndex="0" Tween="False" InnerActionType="NoLoopAction" CurrentAniamtionName="Start1" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="-847613748" Property="ActionValue">
          <InnerActionFrame FrameIndex="0" Tween="False" InnerActionType="LoopAction" CurrentAniamtionName="Start1" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="-925597762" Property="Position">
          <PointFrame FrameIndex="0" Tween="False" X="669.0000" Y="66.0000" />
          <PointFrame FrameIndex="45" X="690.0000" Y="150.0000">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="56" X="757.0000" Y="150.0000">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="96" Tween="False" X="669.0000" Y="66.0000" />
          <PointFrame FrameIndex="105" X="669.0000" Y="66.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="115" Tween="False" X="757.0000" Y="150.0000" />
          <PointFrame FrameIndex="125" X="432.0000" Y="66.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-925597762" Property="Alpha">
          <IntFrame FrameIndex="0" Tween="False" Value="255" />
          <IntFrame FrameIndex="45" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="56" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="96" Tween="False" Value="255" />
          <IntFrame FrameIndex="105" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="114" Tween="False" Value="0" />
          <IntFrame FrameIndex="125" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="idle" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="32" G="178" B="170" />
        </AnimationInfo>
        <AnimationInfo Name="in" StartIndex="50" EndIndex="100">
          <RenderColor A="255" R="240" G="128" B="128" />
        </AnimationInfo>
        <AnimationInfo Name="out" StartIndex="105" EndIndex="115">
          <RenderColor A="255" R="224" G="255" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="2942" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Panel_12" ActionTag="-1107107123" Tag="22286" IconVisible="False" LeftMargin="-540.4521" RightMargin="-539.5479" TopMargin="-168.0000" BottomMargin="-132.0000" ClipAble="False" BackColorAlpha="51" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="300.0000" />
            <Children>
              <AbstractNodeData Name="Image_2" ActionTag="-623367365" Tag="22287" IconVisible="False" LeftMargin="101.0000" RightMargin="669.0000" TopMargin="194.0000" BottomMargin="26.0000" Scale9Enable="True" LeftEage="20" RightEage="45" Scale9OriginX="20" Scale9Width="29" Scale9Height="80" ctype="ImageViewObjectData">
                <Size X="310.0000" Y="80.0000" />
                <Children>
                  <AbstractNodeData Name="LoadingBar_level" ActionTag="-866138309" Tag="22288" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="12.4000" RightMargin="10.6000" TopMargin="10.0000" BottomMargin="10.0000" ProgressInfo="100" ctype="LoadingBarObjectData">
                    <Size X="287.0000" Y="60.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="12.4000" Y="40.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0400" Y="0.5000" />
                    <PreSize X="0.9258" Y="0.7500" />
                    <ImageFileData Type="PlistSubImage" Path="fish_dating2.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_lock" ActionTag="-73315254" Tag="45" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-90.5000" RightMargin="297.5000" TopMargin="-23.2000" BottomMargin="-24.8000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="73" Scale9Height="106" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="103.0000" Y="128.0000" />
                    <Children>
                      <AbstractNodeData Name="FileNode_level" ActionTag="-1564788750" VisibleForFrame="False" Tag="19865" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="51.5000" RightMargin="51.5000" TopMargin="64.0000" BottomMargin="64.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="51.5000" Y="64.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5000" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="ui/Animation/Node_gold.csd" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="BitmapFontLabel_level" ActionTag="1694449401" Tag="4889" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="3.5000" RightMargin="3.5000" TopMargin="27.0000" BottomMargin="11.0000" LabelText="12" ctype="TextBMFontObjectData">
                        <Size X="96.0000" Y="90.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="51.5000" Y="56.0000" />
                        <Scale ScaleX="0.6400" ScaleY="0.6400" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.4375" />
                        <PreSize X="0.9320" Y="0.7031" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_currentLv" ActionTag="129055800" Tag="22290" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="14.0000" RightMargin="14.0000" TopMargin="17.0000" BottomMargin="81.0000" FontSize="30" LabelText="Level" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="75.0000" Y="30.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="51.5000" Y="96.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="0" G="0" B="0" />
                        <PrePosition X="0.5000" Y="0.7500" />
                        <PreSize X="0.7282" Y="0.2344" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-39.0000" Y="39.2000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-0.1258" Y="0.4900" />
                    <PreSize X="0.3323" Y="1.6000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="fish_levelup0.png" Plist="ui.plist" />
                    <PressedFileData Type="PlistSubImage" Path="fish_levelup0.png" Plist="ui.plist" />
                    <NormalFileData Type="PlistSubImage" Path="fish_levelup0.png" Plist="ui.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="LevelBG_1" ActionTag="1654391266" VisibleForFrame="False" Tag="22289" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-90.5000" RightMargin="297.5000" TopMargin="-23.2000" BottomMargin="-24.8000" ctype="SpriteObjectData">
                    <Size X="103.0000" Y="128.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-39.0000" Y="39.2000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-0.1258" Y="0.4900" />
                    <PreSize X="0.3323" Y="1.6000" />
                    <FileData Type="PlistSubImage" Path="fish_levelup0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position X="101.0000" Y="66.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0935" Y="0.2200" />
                <PreSize X="0.2870" Y="0.2667" />
                <FileData Type="PlistSubImage" Path="fish_dating0.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_2_0_0" ActionTag="2113183034" VisibleForFrame="False" Tag="22292" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="777.6000" RightMargin="32.3999" TopMargin="196.0000" BottomMargin="28.0000" Scale9Enable="True" LeftEage="20" RightEage="20" TopEage="11" BottomEage="11" Scale9OriginX="20" Scale9OriginY="11" Scale9Width="27" Scale9Height="28" ctype="ImageViewObjectData">
                <Size X="270.0000" Y="76.0000" />
                <Children>
                  <AbstractNodeData Name="Button_getDiamond" ActionTag="414434911" Tag="22293" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-37.6380" RightMargin="-88.3620" TopMargin="-19.5984" BottomMargin="-24.4016" TouchEnable="True" FontSize="14" Scale9Enable="True" Scale9Width="3" Scale9Height="3" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="396.0000" Y="120.0000" />
                    <Children>
                      <AbstractNodeData Name="store_anniu1_2" ActionTag="626314654" Tag="5416" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-8.9400" RightMargin="299.9400" TopMargin="15.5000" BottomMargin="15.5000" ctype="SpriteObjectData">
                        <Size X="105.0000" Y="89.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="43.5600" Y="60.0000" />
                        <Scale ScaleX="0.8800" ScaleY="1.0200" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1100" Y="0.5000" />
                        <PreSize X="0.2652" Y="0.7417" />
                        <FileData Type="PlistSubImage" Path="store_anniu1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="-37.6380" Y="35.5984" />
                    <Scale ScaleX="0.7700" ScaleY="0.7700" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-0.1394" Y="0.4684" />
                    <PreSize X="1.4667" Y="1.5789" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                    <PressedFileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                    <NormalFileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="BitmapFontLabel_diamond" ActionTag="245623929" Tag="22294" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="60.7000" RightMargin="51.3000" TopMargin="-7.0000" BottomMargin="-7.0000" LabelText="900、" ctype="TextBMFontObjectData">
                    <Size X="158.0000" Y="90.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="218.7000" Y="38.0000" />
                    <Scale ScaleX="0.5200" ScaleY="0.5200" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8100" Y="0.5000" />
                    <PreSize X="0.5852" Y="1.1842" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="img_icon_top_diamond" ActionTag="1377650716" Tag="22295" RotationSkewX="-178.0000" RotationSkewY="-180.0018" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="220.7000" RightMargin="-0.7000" TopMargin="12.5000" BottomMargin="12.5000" ctype="SpriteObjectData">
                    <Size X="50.0000" Y="51.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="245.7000" Y="38.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9100" Y="0.5000" />
                    <PreSize X="0.1852" Y="0.6711" />
                    <FileData Type="PlistSubImage" Path="Money/Baoshi_4.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="FileNode_diamond" Visible="False" ActionTag="2038003185" VisibleForFrame="False" Tag="19721" IconVisible="True" LeftMargin="245.6999" RightMargin="24.3001" TopMargin="38.0000" BottomMargin="38.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="245.6999" Y="38.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9100" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="ui/Animation/Node_gold.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position X="777.6000" Y="66.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7200" Y="0.2200" />
                <PreSize X="0.2500" Y="0.2533" />
                <FileData Type="PlistSubImage" Path="ui_homelevel_3.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_2_0_0_0" ActionTag="-925597762" Tag="22296" IconVisible="False" LeftMargin="669.0000" RightMargin="40.0000" TopMargin="194.0000" BottomMargin="26.0000" Scale9Enable="True" LeftEage="49" RightEage="43" TopEage="11" BottomEage="11" Scale9OriginX="49" Scale9OriginY="11" Scale9Width="31" Scale9Height="58" ctype="ImageViewObjectData">
                <Size X="371.0000" Y="80.0000" />
                <Children>
                  <AbstractNodeData Name="BitmapFontLabel_gold" ActionTag="-340814223" Tag="22298" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="85.8000" RightMargin="74.2000" TopMargin="-5.0000" BottomMargin="-5.0000" LabelText="9000" ctype="TextBMFontObjectData">
                    <Size X="211.0000" Y="90.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="296.8000" Y="40.0000" />
                    <Scale ScaleX="0.5400" ScaleY="0.5400" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8000" Y="0.5000" />
                    <PreSize X="0.5687" Y="1.1250" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_getGold" ActionTag="351241013" Tag="22297" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="-112.0000" TopMargin="-31.4000" BottomMargin="-34.6000" TouchEnable="True" FontSize="14" Scale9Enable="True" Scale9Width="3" Scale9Height="3" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="483.0000" Y="146.0000" />
                    <Children>
                      <AbstractNodeData Name="store_anniu1_2_0" ActionTag="995305871" Tag="5417" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="393.8500" RightMargin="-40.8500" TopMargin="13.8400" BottomMargin="2.1600" ctype="SpriteObjectData">
                        <Size X="130.0000" Y="130.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="458.8500" Y="67.1600" />
                        <Scale ScaleX="1.1900" ScaleY="1.1900" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9500" Y="0.4600" />
                        <PreSize X="0.2692" Y="0.8904" />
                        <FileData Type="PlistSubImage" Path="fish_ui/fish_btn_gold2.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position Y="38.4000" />
                    <Scale ScaleX="0.7700" ScaleY="0.7700" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.4800" />
                    <PreSize X="1.3019" Y="1.8250" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                    <PressedFileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                    <NormalFileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="img_icon_top_gold" ActionTag="1597139122" Tag="22299" RotationSkewX="3.0002" RotationSkewY="2.9999" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.6381" RightMargin="289.3619" TopMargin="4.9400" BottomMargin="8.0600" FlipX="True" ctype="SpriteObjectData">
                    <Size X="66.0000" Y="67.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="48.6381" Y="41.5600" />
                    <Scale ScaleX="0.8300" ScaleY="0.8300" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1311" Y="0.5195" />
                    <PreSize X="0.1779" Y="0.8375" />
                    <FileData Type="PlistSubImage" Path="Money/Gold_6.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="FileNode_gold" Visible="False" ActionTag="-847613748" VisibleForFrame="False" Tag="19729" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="48.6381" RightMargin="322.3619" TopMargin="38.4400" BottomMargin="41.5600" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="48.6381" Y="41.5600" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1311" Y="0.5195" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="ui/Animation/Node_gold.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position X="669.0000" Y="66.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6194" Y="0.2200" />
                <PreSize X="0.3435" Y="0.2667" />
                <FileData Type="PlistSubImage" Path="fish_dating1.png" Plist="ui.plist" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" />
            <Position X="-0.4521" Y="-132.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
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