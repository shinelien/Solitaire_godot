<GameFile>
  <PropertyGroup Name="2020StarBox_pad" Type="Layer" ID="9ed9a2de-404b-4f5b-9aa0-ca2a232f8dac" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="100" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="1481239810" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="15" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1550546683" Property="ActionValue">
          <InnerActionFrame FrameIndex="5" Tween="False" InnerActionType="NoLoopAction" CurrentAniamtionName="Start0" SingleFrameIndex="0" />
          <InnerActionFrame FrameIndex="100" Tween="False" InnerActionType="NoLoopAction" CurrentAniamtionName="-- ALL --" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="1550546683" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="5" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="1550546683" Property="Alpha">
          <IntFrame FrameIndex="5" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="8" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1243799494" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.5000" Y="0.5000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1243799494" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="10" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="45">
          <RenderColor A="255" R="253" G="245" B="230" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="176" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_bg_0" ActionTag="1481239810" Alpha="0" Tag="39064" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentWidthEnabled="True" TopMargin="-120.0159" BottomMargin="-239.9841" TouchEnable="True" StretchHeightEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1800.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="660.0159" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4583" />
            <PreSize X="1.0000" Y="1.2500" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_top_0" ActionTag="1847776331" Tag="39035" IconVisible="False" PositionPercentXEnabled="True" VerticalEdge="TopEdge" TouchEnable="True" StretchHeightEnable="True" ClipAble="False" BackColorAlpha="153" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Node_4" ActionTag="-1243799494" Alpha="0" Tag="39036" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="648.0000" BottomMargin="792.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Node_1" ActionTag="-628250550" Tag="39037" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_1" ActionTag="-2003120184" Tag="39038" IconVisible="False" LeftMargin="-465.0000" RightMargin="-465.0000" TopMargin="-500.0000" BottomMargin="-500.0000" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="90" BottomEage="90" Scale9OriginX="90" Scale9OriginY="90" Scale9Width="207" Scale9Height="296" ctype="ImageViewObjectData">
                        <Size X="930.0000" Y="1000.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="244" B="229" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg4_1_0_0_0" ActionTag="-2016346705" Tag="39039" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-96.5000" RightMargin="-96.5000" TopMargin="-280.9106" BottomMargin="276.9106" ctype="SpriteObjectData">
                        <Size X="193.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="278.9106" />
                        <Scale ScaleX="3.5856" ScaleY="1.2800" />
                        <CColor A="255" R="184" G="177" B="151" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_shop3.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_17" ActionTag="1122942942" Tag="39040" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-285.0000" TopMargin="-587.0000" BottomMargin="425.0000" LeftEage="66" RightEage="66" TopEage="39" BottomEage="39" Scale9OriginX="66" Scale9OriginY="39" Scale9Width="68" Scale9Height="43" ctype="ImageViewObjectData">
                        <Size X="285.0000" Y="162.0000" />
                        <Children>
                          <AbstractNodeData Name="Image_17_0" ActionTag="-1158037707" Tag="39041" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-1.0003" RightMargin="1.0003" FlipX="True" LeftEage="66" RightEage="66" TopEage="39" BottomEage="39" Scale9OriginX="66" Scale9OriginY="39" Scale9Width="68" Scale9Height="43" ctype="ImageViewObjectData">
                            <Size X="285.0000" Y="162.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                            <Position X="283.9997" Y="162.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.9965" Y="1.0000" />
                            <PreSize X="1.0000" Y="1.0000" />
                            <FileData Type="PlistSubImage" Path="Challenge_chuangkoubg0.png" Plist="ui.plist" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                        <Position Y="587.0000" />
                        <Scale ScaleX="1.1900" ScaleY="1.0600" />
                        <CColor A="255" R="255" G="246" B="233" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="Challenge_chuangkoubg0.png" Plist="ui.plist" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_Start" ActionTag="-570982757" Tag="39042" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-250.0000" RightMargin="-250.0000" TopMargin="296.5085" BottomMargin="-446.5085" TouchEnable="True" FontSize="14" LeftEage="100" RightEage="100" TopEage="46" BottomEage="46" Scale9OriginX="100" Scale9OriginY="46" Scale9Width="71" Scale9Height="30" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="150.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_Start" ActionTag="1761994089" Tag="39043" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="160.0000" RightMargin="160.0000" TopMargin="34.5000" BottomMargin="43.5000" FontSize="72" LabelText="Start" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="180.0000" Y="72.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="250.0000" Y="79.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5300" />
                        <PreSize X="0.3600" Y="0.4800" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-371.5085" />
                    <Scale ScaleX="1.0400" ScaleY="1.0400" />
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
                  <AbstractNodeData Name="Button_Open" Visible="False" ActionTag="305627452" Tag="39044" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-250.0000" RightMargin="-250.0000" TopMargin="324.9998" BottomMargin="-474.9998" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="100" RightEage="100" TopEage="46" BottomEage="46" Scale9OriginX="-100" Scale9OriginY="-46" Scale9Width="200" Scale9Height="92" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="150.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_Open" ActionTag="-2096572325" Tag="39045" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="200.0000" RightMargin="200.0000" TopMargin="45.5000" BottomMargin="54.5000" FontSize="50" LabelText="Open" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="100.0000" Y="50.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="250.0000" Y="79.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5300" />
                        <PreSize X="0.2000" Y="0.3333" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-399.9998" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_10" ActionTag="2037970460" Tag="39046" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-112.0000" RightMargin="-112.0000" TopMargin="-562.5003" BottomMargin="507.5003" FontSize="55" LabelText="StartBox" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="224.0000" Y="55.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="535.0003" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="69" G="54" B="40" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_5_0" ActionTag="-1753362836" Tag="39047" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-500.0000" RightMargin="-500.0000" TopMargin="145.5659" BottomMargin="-245.5659" FontSize="50" LabelText="коллекция из игры &#xA;20 звезда открыть ящик " HorizontalAlignmentType="HT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="1000.0000" Y="100.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="-145.5659" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_zh" ActionTag="1174528277" VisibleForFrame="False" Tag="39048" IconVisible="False" LeftMargin="-51.1091" RightMargin="-98.8909" TopMargin="148.6002" BottomMargin="-198.6002" FontSize="50" LabelText="33星星" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="150.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="23.8909" Y="-173.6002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_tw" ActionTag="-1844576965" VisibleForFrame="False" Tag="39049" IconVisible="False" LeftMargin="-51.1100" RightMargin="-98.8900" TopMargin="148.6000" BottomMargin="-198.6000" FontSize="50" LabelText="33星星" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="150.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="23.8900" Y="-173.6000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_en" ActionTag="788353470" VisibleForFrame="False" Tag="39050" IconVisible="False" LeftMargin="-224.4967" RightMargin="-0.5033" TopMargin="148.6001" BottomMargin="-198.6001" FontSize="50" LabelText="21 Crowns" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="225.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-111.9967" Y="-173.6001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_ko" ActionTag="-806405249" Tag="39051" IconVisible="False" LeftMargin="-45.0000" RightMargin="-141.0000" TopMargin="148.6002" BottomMargin="-198.6002" FontSize="50" LabelText="크라운 21" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="186.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="48.0000" Y="-173.6002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_ja" ActionTag="247277920" VisibleForFrame="False" Tag="39052" IconVisible="False" LeftMargin="57.0000" RightMargin="-213.0000" TopMargin="145.1001" BottomMargin="-202.1001" IsCustomSize="True" FontSize="50" LabelText="21つ星" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="156.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="135.0000" Y="-173.6001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_fr" ActionTag="-1519181862" VisibleForFrame="False" Tag="39053" IconVisible="False" LeftMargin="-313.6226" RightMargin="13.6226" TopMargin="205.2038" BottomMargin="-255.2038" FontSize="50" LabelText="21 couronnes" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="300.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-163.6226" Y="-230.2038" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_de" ActionTag="-1651755732" VisibleForFrame="False" Tag="39054" IconVisible="False" LeftMargin="-181.5110" RightMargin="-43.4890" TopMargin="148.6001" BottomMargin="-198.6001" FontSize="50" LabelText="21 Kronen" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="225.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-69.0110" Y="-173.6001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_tr" ActionTag="2029331091" VisibleForFrame="False" Tag="39055" IconVisible="False" LeftMargin="-230.4189" RightMargin="5.4189" TopMargin="210.3028" BottomMargin="-260.3028" FontSize="50" LabelText="21 Taçlar" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="225.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-117.9189" Y="-235.3028" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_StarNum_ru" ActionTag="-84228531" Tag="39056" IconVisible="False" LeftMargin="-342.6150" RightMargin="-32.3850" TopMargin="208.8824" BottomMargin="-258.8824" FontSize="50" LabelText="20 звезда" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="375.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-155.1150" Y="-233.8824" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_close" ActionTag="-786600969" Tag="39057" IconVisible="False" LeftMargin="387.1355" RightMargin="-491.1355" TopMargin="-530.1366" BottomMargin="400.1366" TouchEnable="True" FontSize="72" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="130.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="439.1355" Y="465.1366" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_5_0_0" ActionTag="-451321439" Tag="39058" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-250.0000" RightMargin="-250.0000" TopMargin="-350.0000" BottomMargin="300.0000" FontSize="50" LabelText="宝箱可以获得大量金币" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="500.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="350.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="FileNode_box" ActionTag="1550546683" VisibleForFrame="False" Alpha="0" Tag="39059" IconVisible="True" LeftMargin="40.0000" RightMargin="-40.0000" TopMargin="91.0000" BottomMargin="-91.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="40.0000" Y="-91.0000" />
                    <Scale ScaleX="1.2000" ScaleY="1.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="ui/Animation/NodeBox.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="792.0000" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5500" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="720.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
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