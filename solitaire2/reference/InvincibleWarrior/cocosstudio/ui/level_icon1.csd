<GameFile>
  <PropertyGroup Name="level_icon1" Type="Layer" ID="3ea629f8-4174-4566-aa47-55f7efae51d3" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="120" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="-1894403630" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.9800" Y="0.9800">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="120" X="1.1500" Y="1.1500">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1894403630" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="60" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="120" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-378949010" Property="Alpha">
          <IntFrame FrameIndex="0" Value="76">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="60" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="120" Value="76">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start" StartIndex="0" EndIndex="120">
          <RenderColor A="255" R="255" G="99" B="71" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="193" ctype="GameLayerObjectData">
        <Size X="220.0000" Y="380.0000" />
        <Children>
          <AbstractNodeData Name="Panel_root" ActionTag="1811339634" Tag="79" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="220.0000" Y="380.0000" />
            <Children>
              <AbstractNodeData Name="Text_title" ActionTag="-1937409161" VisibleForFrame="False" Tag="370" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.4280" RightMargin="30.5720" TopMargin="333.0660" BottomMargin="1.9340" FontSize="40" LabelText="赢得积分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="160.0000" Y="45.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="109.4280" Y="24.4340" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="25" G="37" B="47" />
                <PrePosition X="0.4974" Y="0.0643" />
                <PreSize X="0.7273" Y="0.1184" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Level_btn_Level0_23" ActionTag="512309579" Tag="1823" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="7.0000" RightMargin="7.0000" TopMargin="85.0000" BottomMargin="87.0000" ctype="SpriteObjectData">
                <Size X="206.0000" Y="208.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="110.0000" Y="191.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5026" />
                <PreSize X="0.9364" Y="0.5474" />
                <FileData Type="PlistSubImage" Path="Level_btn_Level0.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_go" ActionTag="19354013" Tag="368" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="20.0000" RightMargin="20.0000" TopMargin="90.0000" BottomMargin="110.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="151" Scale9Height="158" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="180.0000" Y="180.0000" />
                <Children>
                  <AbstractNodeData Name="Level_icon1" ActionTag="844708542" Tag="371" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" ctype="SpriteObjectData">
                    <Size X="180.0000" Y="180.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="90.0000" Y="90.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="1.0000" Y="1.0000" />
                    <FileData Type="PlistSubImage" Path="Level_icon1.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_icon0" ActionTag="-1576122401" Tag="369" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-0.5000" RightMargin="-0.5000" ctype="SpriteObjectData">
                    <Size X="181.0000" Y="180.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="90.0000" Y="90.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="1.0056" Y="1.0000" />
                    <FileData Type="PlistSubImage" Path="Level_iconbg0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="110.0000" Y="200.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5263" />
                <PreSize X="0.8182" Y="0.4737" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="PlistSubImage" Path="Level_iconbg0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_star" ActionTag="887085111" Tag="1530" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="110.0000" RightMargin="110.0000" TopMargin="243.2000" BottomMargin="136.8000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Level_star1" ActionTag="-1305050181" Tag="1655" IconVisible="False" LeftMargin="-57.0000" RightMargin="23.0000" TopMargin="-18.5000" BottomMargin="-18.5000" ctype="SpriteObjectData">
                    <Size X="34.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-40.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_star0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_star2" ActionTag="-570062667" Tag="1653" IconVisible="False" LeftMargin="-17.0000" RightMargin="-17.0000" TopMargin="-18.5000" BottomMargin="-18.5000" ctype="SpriteObjectData">
                    <Size X="34.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_star0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_star3" ActionTag="1211246045" Tag="1654" IconVisible="False" LeftMargin="22.9998" RightMargin="-56.9998" TopMargin="-18.5000" BottomMargin="-18.5000" ctype="SpriteObjectData">
                    <Size X="34.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="39.9998" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_star0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_starbg1" ActionTag="1201700645" Tag="1529" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-57.0000" RightMargin="23.0000" TopMargin="-18.5000" BottomMargin="-18.5000" ctype="SpriteObjectData">
                    <Size X="34.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-40.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_star.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_starbg2" ActionTag="-2029597937" Tag="1531" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-17.0000" RightMargin="-17.0000" TopMargin="-18.5000" BottomMargin="-18.5000" ctype="SpriteObjectData">
                    <Size X="34.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_star.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_starbg3" ActionTag="28601832" Tag="1532" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="22.9998" RightMargin="-56.9998" TopMargin="-18.5000" BottomMargin="-18.5000" ctype="SpriteObjectData">
                    <Size X="34.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="39.9998" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_star.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="110.0000" Y="136.8000" />
                <Scale ScaleX="1.2000" ScaleY="1.2000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3600" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Level_complete" Visible="False" ActionTag="-2021597099" VisibleForFrame="False" Tag="3484" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="114.4880" RightMargin="6.5120" TopMargin="82.9300" BottomMargin="198.0700" ctype="SpriteObjectData">
                <Size X="99.0000" Y="99.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="163.9880" Y="247.5700" />
                <Scale ScaleX="0.2344" ScaleY="0.2344" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7454" Y="0.6515" />
                <PreSize X="0.4500" Y="0.2605" />
                <FileData Type="PlistSubImage" Path="Level_complete.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_2" ActionTag="-247376037" Alpha="12" Tag="20" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="16.0000" RightMargin="16.0000" TopMargin="281.5000" BottomMargin="51.5000" Scale9Enable="True" LeftEage="17" RightEage="17" TopEage="19" BottomEage="19" Scale9OriginX="17" Scale9OriginY="19" Scale9Width="18" Scale9Height="22" ctype="ImageViewObjectData">
                <Size X="188.0000" Y="47.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="110.0000" Y="75.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.1974" />
                <PreSize X="0.8545" Y="0.1237" />
                <FileData Type="PlistSubImage" Path="Level_tips.png" Plist="ui1.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_level" ActionTag="-361634539" Tag="30" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="86.5000" RightMargin="86.5000" TopMargin="260.0000" BottomMargin="30.0000" LabelText="1" ctype="TextBMFontObjectData">
                <Size X="47.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="110.0000" Y="75.0000" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.1974" />
                <PreSize X="0.2136" Y="0.2368" />
                <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_select" ActionTag="624791126" Tag="18" IconVisible="True" LeftMargin="109.9992" RightMargin="110.0008" TopMargin="180.0000" BottomMargin="200.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_1_0" ActionTag="-1894403630" Alpha="140" Tag="17" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-100.0000" RightMargin="-100.0000" TopMargin="-100.0000" BottomMargin="-100.0000" Scale9Enable="True" LeftEage="54" RightEage="54" TopEage="77" BottomEage="77" Scale9OriginX="54" Scale9OriginY="77" Scale9Width="48" Scale9Height="78" ctype="ImageViewObjectData">
                    <Size X="200.0000" Y="200.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.1344" ScaleY="1.1344" />
                    <CColor A="255" R="255" G="204" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="card_light0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_1" ActionTag="-378949010" Alpha="174" Tag="16" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-105.0000" RightMargin="-105.0000" TopMargin="-105.0000" BottomMargin="-105.0000" Scale9Enable="True" LeftEage="54" RightEage="54" TopEage="77" BottomEage="77" Scale9OriginX="54" Scale9OriginY="77" Scale9Width="48" Scale9Height="78" ctype="ImageViewObjectData">
                    <Size X="210.0000" Y="210.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="204" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="card_light0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="109.9992" Y="200.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5263" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>