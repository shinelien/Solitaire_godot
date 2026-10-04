<GameFile>
  <PropertyGroup Name="CountLayer" Type="Layer" ID="140316bc-a02b-4c40-8ba1-5144fa9b32d6" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="-805980173" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="25" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-765581172" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.9000" Y="0.9000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-765581172" Property="Alpha">
          <IntFrame FrameIndex="3" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="10" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="255" G="250" B="205" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="86" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="-805980173" Alpha="0" Tag="527" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TopMargin="-779.9041" BottomMargin="-300.0960" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="3000.0000" />
            <AnchorPoint />
            <Position Y="-300.0960" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="-0.1563" />
            <PreSize X="1.0000" Y="1.5625" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_2" Visible="False" ActionTag="-1378864440" VisibleForFrame="False" Tag="18460" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="-596.0520" RightMargin="-633.9600" TopMargin="-635.5200" BottomMargin="-264.5760" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="2310.0120" Y="2820.0959" />
            <AnchorPoint />
            <Position X="-596.0520" Y="-264.5760" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.5519" Y="-0.1378" />
            <PreSize X="2.1389" Y="1.4688" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_count" ActionTag="959366185" Tag="87" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Node_2" ActionTag="-765581172" Alpha="0" Tag="2066" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="883.2000" BottomMargin="1036.8000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_2" ActionTag="1602979764" Tag="18464" IconVisible="False" LeftMargin="-450.0017" RightMargin="-449.9983" TopMargin="-660.0000" BottomMargin="-740.0000" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="90" BottomEage="90" Scale9OriginX="90" Scale9OriginY="90" Scale9Width="207" Scale9Height="296" ctype="ImageViewObjectData">
                    <Size X="900.0000" Y="1400.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-0.0017" Y="-40.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="PageView_container" ActionTag="-1669724663" Tag="2115" IconVisible="False" LeftMargin="-425.0001" RightMargin="-424.9999" TopMargin="-523.9978" BottomMargin="-780.0022" TouchEnable="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" ctype="PageViewObjectData">
                    <Size X="850.0000" Y="1304.0000" />
                    <Children>
                      <AbstractNodeData Name="panel_num_1" ActionTag="-120090225" Tag="2437" IconVisible="False" RightMargin="850.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                        <Size X="850.0000" Y="1304.0000" />
                        <Children>
                          <AbstractNodeData Name="Node_data" ActionTag="-731319411" Tag="2108" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="425.0000" RightMargin="425.0000" TopMargin="560.7200" BottomMargin="743.2800" ctype="SingleNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <Children>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_0" ActionTag="366549988" Tag="2657" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="-436.0000" BottomMargin="356.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0" ActionTag="-733205484" Tag="2658" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="575.0000" TopMargin="20.4560" BottomMargin="19.5440" FontSize="40" LabelText="最高得分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="160.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="39.5440" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.4943" />
                                    <PreSize X="0.2133" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_9" ActionTag="-179137302" Tag="2659" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="645.0250" RightMargin="12.9750" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="4444" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="92.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="737.0250" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9827" Y="0.5000" />
                                    <PreSize X="0.1227" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="436.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Node_win" ActionTag="-144469529" Tag="2436" IconVisible="True" LeftMargin="-200.0000" RightMargin="200.0000" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="-1752223831" Tag="2435" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
                                    <Size X="170.0000" Y="170.0000" />
                                    <AnchorPoint ScaleX="0.4236" ScaleY="0.4819" />
                                    <Position X="-12.9895" Y="-3.0846" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <FileData Type="PlistSubImage" Path="game_ui statistics0.png" Plist="ui.plist" />
                                    <BlendFunc Src="1" Dst="771" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_1" ActionTag="542305820" Tag="2442" IconVisible="False" LeftMargin="-71.9998" RightMargin="-72.0002" TopMargin="102.0000" BottomMargin="-138.0000" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="144.0000" Y="36.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position X="0.0002" Y="-120.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="Text_3" ActionTag="-800418061" Tag="2443" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-142.0000" BottomMargin="102.0000" FontSize="40" LabelText="胜利局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="160.0000" Y="40.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position Y="122.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint />
                                <Position X="-200.0000" Y="180.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Node_lose" ActionTag="168306030" Tag="2642" IconVisible="True" LeftMargin="199.9999" RightMargin="-199.9999" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="-1179222648" Tag="2643" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
                                    <Size X="170.0000" Y="170.0000" />
                                    <AnchorPoint ScaleX="0.4236" ScaleY="0.4819" />
                                    <Position X="-12.9895" Y="-3.0846" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <FileData Type="PlistSubImage" Path="game_ui statistics0.png" Plist="ui.plist" />
                                    <BlendFunc Src="1" Dst="771" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_2" ActionTag="461790778" Tag="2644" IconVisible="False" LeftMargin="-71.9997" RightMargin="-72.0003" TopMargin="102.0002" BottomMargin="-138.0002" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="144.0000" Y="36.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position X="0.0003" Y="-120.0002" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="Text_3_0" ActionTag="490271580" Tag="2646" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-140.5000" BottomMargin="100.5000" FontSize="40" LabelText="失败局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="160.0000" Y="40.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position Y="120.5000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint />
                                <Position X="199.9999" Y="180.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1" ActionTag="-997759563" Tag="2112" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="-10.0000" BottomMargin="-70.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0" ActionTag="1113984940" Tag="2449" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_4" ActionTag="258380099" Tag="2450" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="115.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.1533" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="10.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_0_0" ActionTag="-1944840015" Tag="2113" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0760" RightMargin="-375.0760" TopMargin="70.0000" BottomMargin="-150.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.1521" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0" ActionTag="1860849763" Tag="2647" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0030" RightMargin="495.1490" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0030" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3199" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_5" ActionTag="-891420507" Tag="2648" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.1490" RightMargin="15.0031" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="115.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.1490" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.1533" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-70.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0" ActionTag="-1763692870" Tag="2114" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="150.0000" BottomMargin="-230.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0" ActionTag="889672300" Tag="2649" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最少步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_6" ActionTag="61748354" Tag="2650" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-150.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0" ActionTag="2085285535" Tag="2651" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="230.0000" BottomMargin="-310.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0" ActionTag="1175738759" Tag="2652" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最多步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_7" ActionTag="1620254880" Tag="2653" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-230.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0" ActionTag="-1435693169" Tag="2654" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="310.0000" BottomMargin="-390.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0" ActionTag="-1199523045" Tag="2655" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="无撤回胜利" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="200.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.2667" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_8" ActionTag="-1603057864" Tag="2656" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-310.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1" ActionTag="551713707" Tag="2660" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="390.0000" BottomMargin="-470.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0" ActionTag="-1703941753" Tag="2661" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="当前连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_10" ActionTag="-463588998" Tag="2662" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-390.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0" ActionTag="-227558766" Tag="2663" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="470.0000" BottomMargin="-550.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0" ActionTag="960009932" Tag="2664" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最高连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_11" ActionTag="1138495466" Tag="2665" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-470.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_0" ActionTag="704810952" Tag="2666" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="550.0000" BottomMargin="-630.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0_0" ActionTag="215862000" Tag="2667" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="总游戏时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="200.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.2667" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_12" ActionTag="922495319" Tag="2668" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="115.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.1533" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-550.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_1" ActionTag="-305608812" VisibleForFrame="False" Tag="6894" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="630.0000" BottomMargin="-710.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_VegasScore" ActionTag="-441796136" Tag="6895" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="375.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="维加斯最高累计分数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="360.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.4800" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_13" ActionTag="-1750484193" Tag="6896" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-630.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Image_3" ActionTag="-1073637342" Tag="502" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-314.5000" RightMargin="-314.5000" TopMargin="-529.5000" BottomMargin="446.5000" Scale9Enable="True" LeftEage="253" RightEage="253" TopEage="20" BottomEage="20" Scale9OriginX="253" Scale9OriginY="20" Scale9Width="262" Scale9Height="21" ctype="ImageViewObjectData">
                                <Size X="629.0000" Y="83.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position Y="488.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="0" G="0" B="0" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Text_2" ActionTag="459979983" Tag="2669" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-150.0000" RightMargin="-150.0000" TopMargin="-508.0000" BottomMargin="468.0000" FontSize="40" LabelText="Noraml - 1 card" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="300.0000" Y="40.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position Y="488.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Sprite_4_0_0" ActionTag="2095540584" Tag="330" IconVisible="False" LeftMargin="-287.0000" RightMargin="113.0000" TopMargin="-267.0000" BottomMargin="93.0000" ctype="SpriteObjectData">
                                <Size X="174.0000" Y="174.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="-200.0000" Y="180.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game_ui statistics3.png" Plist="ui.plist" />
                                <BlendFunc Src="1" Dst="771" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Sprite_4_0" ActionTag="-1764184362" Tag="329" IconVisible="False" LeftMargin="112.9999" RightMargin="-286.9999" TopMargin="-266.9999" BottomMargin="92.9999" ctype="SpriteObjectData">
                                <Size X="174.0000" Y="174.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="199.9999" Y="179.9999" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game_ui statistics3.png" Plist="ui.plist" />
                                <BlendFunc Src="1" Dst="771" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint />
                            <Position X="425.0000" Y="743.2800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5700" />
                            <PreSize X="0.0000" Y="0.0000" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.5000" Y="1.0000" />
                        <SingleColor A="255" R="144" G="238" B="144" />
                        <FirstColor A="255" R="150" G="200" B="255" />
                        <EndColor A="255" R="255" G="255" B="255" />
                        <ColorVector ScaleY="1.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="panel_num_2" ActionTag="-1602155755" ZOrder="1" Tag="2683" IconVisible="False" LeftMargin="850.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                        <Size X="850.0000" Y="1304.0000" />
                        <Children>
                          <AbstractNodeData Name="Node_data" ActionTag="-33906992" Tag="2684" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="425.0000" RightMargin="425.0000" TopMargin="560.7200" BottomMargin="743.2800" ctype="SingleNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <Children>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_0" ActionTag="-386548638" Tag="2685" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="-436.0001" BottomMargin="356.0001" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_1" ActionTag="-835979245" Tag="2686" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="37.5000" RightMargin="560.5000" TopMargin="21.4560" BottomMargin="20.5440" FontSize="38" LabelText="最高得分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="152.0000" Y="38.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="37.5000" Y="39.5440" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0500" Y="0.4943" />
                                    <PreSize X="0.2027" Y="0.4750" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_9" ActionTag="567175915" Tag="2687" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="645.0250" RightMargin="12.9750" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="4444" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="92.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="737.0250" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9827" Y="0.5000" />
                                    <PreSize X="0.1227" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="436.0001" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Node_win" ActionTag="-1012341369" Tag="2688" IconVisible="True" LeftMargin="-200.0000" RightMargin="200.0000" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="-1527780803" Tag="2689" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
                                    <Size X="170.0000" Y="170.0000" />
                                    <AnchorPoint ScaleX="0.4236" ScaleY="0.4819" />
                                    <Position X="-12.9895" Y="-3.0846" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <FileData Type="PlistSubImage" Path="game_ui statistics0.png" Plist="ui.plist" />
                                    <BlendFunc Src="1" Dst="771" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_1" ActionTag="-656303613" Tag="2690" IconVisible="False" LeftMargin="-71.9997" RightMargin="-72.0003" TopMargin="102.0002" BottomMargin="-138.0002" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="144.0000" Y="36.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position X="0.0003" Y="-120.0002" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="Text_3_2" ActionTag="-1977163282" Tag="2692" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-140.5001" BottomMargin="100.5001" FontSize="40" LabelText="胜利局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="160.0000" Y="40.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position Y="120.5001" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint />
                                <Position X="-200.0000" Y="180.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Node_lose" ActionTag="-1997427430" Tag="2693" IconVisible="True" LeftMargin="199.9999" RightMargin="-199.9999" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="398817781" Tag="2694" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
                                    <Size X="170.0000" Y="170.0000" />
                                    <AnchorPoint ScaleX="0.4236" ScaleY="0.4819" />
                                    <Position X="-12.9895" Y="-3.0846" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <FileData Type="PlistSubImage" Path="game_ui statistics0.png" Plist="ui.plist" />
                                    <BlendFunc Src="1" Dst="771" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_2" ActionTag="178651339" Tag="2695" IconVisible="False" LeftMargin="-71.9997" RightMargin="-72.0003" TopMargin="102.0002" BottomMargin="-138.0002" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="144.0000" Y="36.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position X="0.0003" Y="-120.0002" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="Text_3_0_1" ActionTag="1690716731" Tag="2697" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-140.5001" BottomMargin="100.5001" FontSize="40" LabelText="失败局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="160.0000" Y="40.0000" />
                                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                    <Position Y="120.5001" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition />
                                    <PreSize X="0.0000" Y="0.0000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint />
                                <Position X="199.9999" Y="180.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1" ActionTag="507328148" Tag="2698" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" BottomMargin="-80.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_1" ActionTag="1710897067" Tag="2699" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_4" ActionTag="-2008304830" Tag="2700" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="115.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.1533" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_0_0" ActionTag="669805926" Tag="2701" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0760" RightMargin="-375.0760" TopMargin="80.0000" BottomMargin="-160.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.1521" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_1" ActionTag="1765793273" Tag="2702" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0030" RightMargin="495.1490" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0030" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3199" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_5" ActionTag="880927158" Tag="2703" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.1490" RightMargin="15.0031" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="115.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.1490" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.1533" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-80.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0" ActionTag="435519292" Tag="2704" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="160.0000" BottomMargin="-240.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_1" ActionTag="411083090" Tag="2705" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最少步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_6" ActionTag="1337425690" Tag="2706" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-160.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0" ActionTag="393796060" Tag="2707" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="240.0000" BottomMargin="-320.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_1" ActionTag="1249437289" Tag="2708" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最多步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_7" ActionTag="-217801326" Tag="2709" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-240.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0" ActionTag="1598342084" Tag="2710" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="320.0000" BottomMargin="-400.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_1" ActionTag="580689594" Tag="2711" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="无撤回胜利" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="200.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.2667" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_8" ActionTag="1237247533" Tag="2712" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-320.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1" ActionTag="-2059271195" Tag="2713" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="400.0000" BottomMargin="-480.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_1" ActionTag="1382098452" Tag="2714" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="当前连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_10" ActionTag="-974481285" Tag="2715" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-400.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0" ActionTag="-1431912016" Tag="2716" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="480.0000" BottomMargin="-560.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0_1" ActionTag="805756005" Tag="2717" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最高连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="240.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.3200" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_11" ActionTag="1431876748" Tag="2718" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-480.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_0" ActionTag="-237150315" Tag="2719" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="560.0000" BottomMargin="-640.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0_0_1" ActionTag="2039222452" Tag="2720" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="总游戏时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="200.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.2667" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_12" ActionTag="-569693303" Tag="2721" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="115.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.1533" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-560.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_1" ActionTag="992183422" VisibleForFrame="False" Tag="6897" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="640.0000" BottomMargin="-720.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_VegasScore" ActionTag="-1613179946" Tag="6898" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="375.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="维加斯最高累计分数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="360.0000" Y="40.0000" />
                                    <AnchorPoint ScaleY="0.5000" />
                                    <Position X="15.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.0200" Y="0.5000" />
                                    <PreSize X="0.4800" Y="0.5000" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                  <AbstractNodeData Name="atlasLabel_13" ActionTag="-1455534139" Tag="6899" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                    <Size X="23.0000" Y="45.0000" />
                                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                    <Position X="735.0000" Y="40.0000" />
                                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                    <CColor A="255" R="255" G="255" B="255" />
                                    <PrePosition X="0.9800" Y="0.5000" />
                                    <PreSize X="0.0307" Y="0.5625" />
                                    <OutlineColor A="255" R="255" G="0" B="0" />
                                    <ShadowColor A="255" R="110" G="110" B="110" />
                                  </AbstractNodeData>
                                </Children>
                                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                                <Position Y="-640.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <SingleColor A="255" R="0" G="0" B="0" />
                                <FirstColor A="255" R="150" G="200" B="255" />
                                <EndColor A="255" R="255" G="255" B="255" />
                                <ColorVector ScaleY="1.0000" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Sprite_4_0_1" ActionTag="-637197797" Tag="331" IconVisible="False" LeftMargin="112.9999" RightMargin="-286.9999" TopMargin="-266.9999" BottomMargin="92.9999" ctype="SpriteObjectData">
                                <Size X="174.0000" Y="174.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="199.9999" Y="179.9999" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game_ui statistics3.png" Plist="ui.plist" />
                                <BlendFunc Src="1" Dst="771" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Sprite_4_0_0_0" ActionTag="-1912632265" Tag="332" IconVisible="False" LeftMargin="-287.0002" RightMargin="113.0002" TopMargin="-266.9999" BottomMargin="92.9999" ctype="SpriteObjectData">
                                <Size X="174.0000" Y="174.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="-200.0002" Y="179.9999" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game_ui statistics3.png" Plist="ui.plist" />
                                <BlendFunc Src="1" Dst="771" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Image_3_0" ActionTag="-57868207" Tag="503" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-314.5000" RightMargin="-314.5000" TopMargin="-529.5001" BottomMargin="446.5001" Scale9Enable="True" LeftEage="253" RightEage="253" TopEage="20" BottomEage="20" Scale9OriginX="253" Scale9OriginY="20" Scale9Width="262" Scale9Height="21" ctype="ImageViewObjectData">
                                <Size X="629.0000" Y="83.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position Y="488.0001" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="0" G="0" B="0" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Text_2_1" ActionTag="-1768711453" Tag="2722" IconVisible="False" LeftMargin="-153.1050" RightMargin="-146.8950" TopMargin="-508.0000" BottomMargin="468.0000" FontSize="40" LabelText="Noraml - 3 card" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="300.0000" Y="40.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="-3.1050" Y="488.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint />
                            <Position X="425.0000" Y="743.2800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5700" />
                            <PreSize X="0.0000" Y="0.0000" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="850.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" />
                        <PreSize X="0.5000" Y="1.0000" />
                        <SingleColor A="255" R="139" G="105" B="20" />
                        <FirstColor A="255" R="150" G="200" B="255" />
                        <EndColor A="255" R="255" G="255" B="255" />
                        <ColorVector ScaleY="1.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" />
                    <Position X="-0.0001" Y="-780.0022" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <SingleColor A="255" R="150" G="150" B="100" />
                    <FirstColor A="255" R="150" G="150" B="100" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Sprite_2" ActionTag="-1457039656" Tag="3127" IconVisible="False" LeftMargin="-28.0000" RightMargin="12.0000" TopMargin="-538.0000" BottomMargin="522.0000" ctype="SpriteObjectData">
                    <Size X="16.0000" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-20.0000" Y="530.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_ui statistics1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Sprite_3" ActionTag="-1452317565" Tag="3128" IconVisible="False" LeftMargin="12.0000" RightMargin="-28.0000" TopMargin="-538.0000" BottomMargin="522.0000" ctype="SpriteObjectData">
                    <Size X="16.0000" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="20.0000" Y="530.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_ui statistics2.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_1" ActionTag="1584291328" Tag="180" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-100.0000" RightMargin="-100.0000" TopMargin="-611.0000" BottomMargin="561.0000" FontSize="50" LabelText="游戏统计" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="200.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="586.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_close" ActionTag="1475730785" Tag="1793" IconVisible="False" LeftMargin="377.9918" RightMargin="-481.9918" TopMargin="-681.6316" BottomMargin="551.6316" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="130.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="429.9918" Y="616.6316" />
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
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="1036.8000" />
                <Scale ScaleX="0.9000" ScaleY="0.9000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5400" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
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