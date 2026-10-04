<GameFile>
  <PropertyGroup Name="CountLayer_pad" Type="Layer" ID="f6347def-b23d-4fa6-82b6-2b9d2ccdcfb3" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="734534248" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="25" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-346071288" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.6000" Y="0.6000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-346071288" Property="Alpha">
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
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="734534248" Alpha="0" Tag="40150" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TopMargin="-584.9280" BottomMargin="-225.0720" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="2250.0000" />
            <AnchorPoint />
            <Position Y="-225.0720" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="-0.1563" />
            <PreSize X="1.0000" Y="1.5625" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_2" Visible="False" ActionTag="1281871750" VisibleForFrame="False" Tag="40149" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="-596.0520" RightMargin="-633.9600" TopMargin="-476.6400" BottomMargin="-198.4320" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="2310.0120" Y="2115.0720" />
            <AnchorPoint />
            <Position X="-596.0520" Y="-198.4320" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.5519" Y="-0.1378" />
            <PreSize X="2.1389" Y="1.4688" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_count" ActionTag="-1462158934" Tag="40053" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Node_2" ActionTag="-346071288" Alpha="0" Tag="40054" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="662.4000" BottomMargin="777.6000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_2" ActionTag="357067759" Tag="40055" IconVisible="False" LeftMargin="-450.0017" RightMargin="-449.9983" TopMargin="-660.0000" BottomMargin="-740.0000" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="90" BottomEage="90" Scale9OriginX="90" Scale9OriginY="90" Scale9Width="207" Scale9Height="296" ctype="ImageViewObjectData">
                    <Size X="900.0000" Y="1400.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-0.0017" Y="-40.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="PageView_container" ActionTag="-1885544144" Tag="40056" IconVisible="False" LeftMargin="-425.0001" RightMargin="-424.9999" TopMargin="-523.9978" BottomMargin="-780.0022" TouchEnable="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" ctype="PageViewObjectData">
                    <Size X="850.0000" Y="1304.0000" />
                    <Children>
                      <AbstractNodeData Name="panel_num_1" ActionTag="-1623046636" Tag="40057" IconVisible="False" RightMargin="850.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                        <Size X="850.0000" Y="1304.0000" />
                        <Children>
                          <AbstractNodeData Name="Node_data" ActionTag="2110638601" Tag="40058" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="425.0000" RightMargin="425.0000" TopMargin="560.7200" BottomMargin="743.2800" ctype="SingleNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <Children>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_0" ActionTag="761802224" Tag="40059" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="-436.0000" BottomMargin="356.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0" ActionTag="-349782838" Tag="40060" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="575.0000" TopMargin="20.4560" BottomMargin="19.5440" FontSize="40" LabelText="最高得分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_9" ActionTag="-1722873760" Tag="40061" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="645.0250" RightMargin="12.9750" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="4444" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Node_win" ActionTag="-2076762634" Tag="40062" IconVisible="True" LeftMargin="-200.0000" RightMargin="200.0000" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="1962474065" Tag="40063" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_1" ActionTag="-394840587" Tag="40064" IconVisible="False" LeftMargin="-71.9998" RightMargin="-72.0002" TopMargin="102.0000" BottomMargin="-138.0000" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="Text_3" ActionTag="-811372262" Tag="40065" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-142.0000" BottomMargin="102.0000" FontSize="40" LabelText="胜利局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Node_lose" ActionTag="1510461509" Tag="40066" IconVisible="True" LeftMargin="199.9999" RightMargin="-199.9999" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="118427767" Tag="40067" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_2" ActionTag="1523534077" Tag="40068" IconVisible="False" LeftMargin="-71.9997" RightMargin="-72.0003" TopMargin="102.0002" BottomMargin="-138.0002" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="Text_3_0" ActionTag="-956113024" Tag="40069" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-140.5000" BottomMargin="100.5000" FontSize="40" LabelText="失败局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1" ActionTag="-1693808301" Tag="40070" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="-10.0000" BottomMargin="-70.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0" ActionTag="-1592431831" Tag="40071" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_4" ActionTag="1424051774" Tag="40072" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_0_0" ActionTag="-1966729622" Tag="40073" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0760" RightMargin="-375.0760" TopMargin="70.0000" BottomMargin="-150.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.1521" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0" ActionTag="-1104934654" Tag="40074" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0030" RightMargin="495.1490" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_5" ActionTag="-1850891246" Tag="40075" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.1490" RightMargin="15.0031" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0" ActionTag="-1640146453" Tag="40076" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="150.0000" BottomMargin="-230.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0" ActionTag="-862422211" Tag="40077" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最少步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_6" ActionTag="1277470213" Tag="40078" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0" ActionTag="785240881" Tag="40079" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="230.0000" BottomMargin="-310.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0" ActionTag="785743074" Tag="40080" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最多步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_7" ActionTag="-1526946505" Tag="40081" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0" ActionTag="1767331185" Tag="40082" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="310.0000" BottomMargin="-390.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0" ActionTag="-1507994401" Tag="40083" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="无撤回胜利" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_8" ActionTag="542348456" Tag="40084" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1" ActionTag="1037435061" Tag="40085" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="390.0000" BottomMargin="-470.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0" ActionTag="-784031968" Tag="40086" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="当前连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_10" ActionTag="-1195887360" Tag="40087" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0" ActionTag="-220893215" Tag="40088" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="470.0000" BottomMargin="-550.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0" ActionTag="1641018654" Tag="40089" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最高连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_11" ActionTag="-1992505316" Tag="40090" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_0" ActionTag="-1242575871" Tag="40091" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="550.0000" BottomMargin="-630.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0_0" ActionTag="-1236271268" Tag="40092" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="总游戏时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_12" ActionTag="-578751147" Tag="40093" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_1" ActionTag="1663377571" VisibleForFrame="False" Tag="40094" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="630.0000" BottomMargin="-710.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_VegasScore" ActionTag="-1101320559" Tag="40095" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="375.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="维加斯最高累计分数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_13" ActionTag="-834507468" Tag="40096" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Image_3" ActionTag="329242554" Tag="40097" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-314.5000" RightMargin="-314.5000" TopMargin="-529.5000" BottomMargin="446.5000" Scale9Enable="True" LeftEage="253" RightEage="253" TopEage="20" BottomEage="20" Scale9OriginX="253" Scale9OriginY="20" Scale9Width="262" Scale9Height="21" ctype="ImageViewObjectData">
                                <Size X="629.0000" Y="83.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position Y="488.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="0" G="0" B="0" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Text_2" ActionTag="671945213" Tag="40098" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-150.0000" RightMargin="-150.0000" TopMargin="-508.0000" BottomMargin="468.0000" FontSize="40" LabelText="Noraml - 1 card" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Sprite_4_0_0" ActionTag="-1553622495" Tag="40099" IconVisible="False" LeftMargin="-287.0000" RightMargin="113.0000" TopMargin="-267.0000" BottomMargin="93.0000" ctype="SpriteObjectData">
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
                              <AbstractNodeData Name="Sprite_4_0" ActionTag="-1393187152" Tag="40100" IconVisible="False" LeftMargin="112.9999" RightMargin="-286.9999" TopMargin="-266.9999" BottomMargin="92.9999" ctype="SpriteObjectData">
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
                      <AbstractNodeData Name="panel_num_2" ActionTag="567247186" ZOrder="1" Tag="40101" IconVisible="False" LeftMargin="850.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                        <Size X="850.0000" Y="1304.0000" />
                        <Children>
                          <AbstractNodeData Name="Node_data" ActionTag="767795319" Tag="40102" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="425.0000" RightMargin="425.0000" TopMargin="560.7200" BottomMargin="743.2800" ctype="SingleNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <Children>
                              <AbstractNodeData Name="Panel_1_1_0_0_0_0" ActionTag="1627740280" Tag="40103" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="-436.0001" BottomMargin="356.0001" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_1" ActionTag="1562755494" Tag="40104" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="37.5000" RightMargin="560.5000" TopMargin="21.4560" BottomMargin="20.5440" FontSize="38" LabelText="最高得分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_9" ActionTag="-1856631796" Tag="40105" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="645.0250" RightMargin="12.9750" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="4444" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Node_win" ActionTag="-1380533682" Tag="40106" IconVisible="True" LeftMargin="-200.0000" RightMargin="200.0000" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="-2020716003" Tag="40107" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_1" ActionTag="-277423778" Tag="40108" IconVisible="False" LeftMargin="-71.9997" RightMargin="-72.0003" TopMargin="102.0002" BottomMargin="-138.0002" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="Text_3_2" ActionTag="-1554774391" Tag="40109" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-140.5001" BottomMargin="100.5001" FontSize="40" LabelText="胜利局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Node_lose" ActionTag="-1300547918" Tag="40110" IconVisible="True" LeftMargin="199.9999" RightMargin="-199.9999" TopMargin="-180.0000" BottomMargin="180.0000" ctype="SingleNodeObjectData">
                                <Size X="0.0000" Y="0.0000" />
                                <Children>
                                  <AbstractNodeData Name="Sprite_1" ActionTag="450199245" Tag="40111" IconVisible="False" LeftMargin="-85.0015" RightMargin="-84.9985" TopMargin="-84.9924" BottomMargin="-85.0076" ctype="SpriteObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_2" ActionTag="171436914" Tag="40112" IconVisible="False" LeftMargin="-71.9997" RightMargin="-72.0003" TopMargin="102.0002" BottomMargin="-138.0002" FontSize="36" LabelText="10 (60%)" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="Text_3_0_1" ActionTag="-1300963653" Tag="40113" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-80.0000" RightMargin="-80.0000" TopMargin="-140.5001" BottomMargin="100.5001" FontSize="40" LabelText="失败局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1" ActionTag="-62475761" Tag="40114" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" BottomMargin="-80.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_1" ActionTag="1896108606" Tag="40115" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_4" ActionTag="-1412212360" Tag="40116" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_0_0" ActionTag="2013771030" Tag="40117" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0760" RightMargin="-375.0760" TopMargin="80.0000" BottomMargin="-160.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.1521" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_1" ActionTag="-1118029319" Tag="40118" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0030" RightMargin="495.1490" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最快胜利时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_5" ActionTag="-1641618825" Tag="40119" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.1490" RightMargin="15.0031" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0" ActionTag="948365182" Tag="40120" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="160.0000" BottomMargin="-240.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_1" ActionTag="-132514782" Tag="40121" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最少步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_6" ActionTag="1924866420" Tag="40122" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0" ActionTag="-990568527" Tag="40123" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="240.0000" BottomMargin="-320.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_1" ActionTag="1683733000" Tag="40124" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="胜利最多步数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_7" ActionTag="-1799245829" Tag="40125" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0" ActionTag="1509241218" Tag="40126" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="320.0000" BottomMargin="-400.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_1" ActionTag="1591554191" Tag="40127" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="无撤回胜利" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_8" ActionTag="354140712" Tag="40128" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1" ActionTag="-2074558043" Tag="40129" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="400.0000" BottomMargin="-480.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_1" ActionTag="794261490" Tag="40130" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="当前连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_10" ActionTag="-51428696" Tag="40131" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0" ActionTag="1451990006" Tag="40132" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="480.0000" BottomMargin="-560.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0_1" ActionTag="315505152" Tag="40133" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="495.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="最高连胜局数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_11" ActionTag="-1390821392" Tag="40134" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_0" ActionTag="-2126801261" Tag="40135" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="560.0000" BottomMargin="-640.0000" ClipAble="False" BackColorAlpha="25" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_3_1_0_0_0_0_0_0_0_0_0_0_1" ActionTag="-1367707175" Tag="40136" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="535.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="总游戏时间" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_12" ActionTag="204311978" Tag="40137" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="620.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="00:00" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Panel_1_1_0_0_0_1_0_1" ActionTag="603608800" VisibleForFrame="False" Tag="40138" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-375.0000" RightMargin="-375.0000" TopMargin="640.0000" BottomMargin="-720.0000" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                                <Size X="750.0000" Y="80.0000" />
                                <Children>
                                  <AbstractNodeData Name="Text_VegasScore" ActionTag="-1319605108" Tag="40139" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="15.0000" RightMargin="375.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="40" LabelText="维加斯最高累计分数" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                                  <AbstractNodeData Name="atlasLabel_13" ActionTag="130079182" Tag="40140" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="712.0000" RightMargin="15.0000" TopMargin="17.5000" BottomMargin="17.5000" FontSize="45" LabelText="0" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                              <AbstractNodeData Name="Sprite_4_0_1" ActionTag="-964729895" Tag="40141" IconVisible="False" LeftMargin="112.9999" RightMargin="-286.9999" TopMargin="-266.9999" BottomMargin="92.9999" ctype="SpriteObjectData">
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
                              <AbstractNodeData Name="Sprite_4_0_0_0" ActionTag="-928865327" Tag="40142" IconVisible="False" LeftMargin="-287.0002" RightMargin="113.0002" TopMargin="-266.9999" BottomMargin="92.9999" ctype="SpriteObjectData">
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
                              <AbstractNodeData Name="Image_3_0" ActionTag="1855167909" Tag="40143" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-314.5000" RightMargin="-314.5000" TopMargin="-529.5001" BottomMargin="446.5001" Scale9Enable="True" LeftEage="253" RightEage="253" TopEage="20" BottomEage="20" Scale9OriginX="253" Scale9OriginY="20" Scale9Width="262" Scale9Height="21" ctype="ImageViewObjectData">
                                <Size X="629.0000" Y="83.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position Y="488.0001" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="0" G="0" B="0" />
                                <PrePosition />
                                <PreSize X="0.0000" Y="0.0000" />
                                <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Text_2_1" ActionTag="453377459" Tag="40144" IconVisible="False" LeftMargin="-153.1050" RightMargin="-146.8950" TopMargin="-508.0000" BottomMargin="468.0000" FontSize="40" LabelText="Noraml - 3 card" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                  <AbstractNodeData Name="Sprite_2" ActionTag="262966754" Tag="40145" IconVisible="False" LeftMargin="-28.0000" RightMargin="12.0000" TopMargin="-538.0000" BottomMargin="522.0000" ctype="SpriteObjectData">
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
                  <AbstractNodeData Name="Sprite_3" ActionTag="674887937" Tag="40146" IconVisible="False" LeftMargin="12.0000" RightMargin="-28.0000" TopMargin="-538.0000" BottomMargin="522.0000" ctype="SpriteObjectData">
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
                  <AbstractNodeData Name="Text_1" ActionTag="133778386" Tag="40147" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-100.0000" RightMargin="-100.0000" TopMargin="-611.0000" BottomMargin="561.0000" FontSize="50" LabelText="游戏统计" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
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
                  <AbstractNodeData Name="btn_close" ActionTag="-264068568" Tag="40148" IconVisible="False" LeftMargin="377.9918" RightMargin="-481.9918" TopMargin="-681.6316" BottomMargin="551.6316" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
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
                <Position X="540.0000" Y="777.6000" />
                <Scale ScaleX="0.6000" ScaleY="0.6000" />
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