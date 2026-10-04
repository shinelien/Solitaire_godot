<GameFile>
  <PropertyGroup Name="2021FishShop_pad" Type="Layer" ID="a402d504-18db-48ab-876a-5a0c2076938d" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="15" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="253604801" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="15" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-158556688" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.8000" Y="0.8000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-158556688" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="6" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="20">
          <RenderColor A="255" R="250" G="240" B="230" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="17339" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1770.0000" />
        <Children>
          <AbstractNodeData Name="Panel_bg_0" ActionTag="253604801" Tag="10631" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TopMargin="-221.2500" BottomMargin="-221.2500" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="2212.5000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="885.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.2500" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_top_0" ActionTag="-158556688" Tag="17670" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="0.4320" RightMargin="-0.4320" TouchEnable="True" ClipAble="False" BackColorAlpha="153" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1770.0000" />
            <Children>
              <AbstractNodeData Name="Node_6" ActionTag="274363392" Tag="12582" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="885.0000" BottomMargin="885.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_2" ActionTag="-1659407269" Tag="7672" RotationSkewX="180.0000" RotationSkewY="180.0000" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-362.0000" RightMargin="-362.0000" TopMargin="-588.6508" BottomMargin="419.6508" TouchEnable="True" Scale9Enable="True" LeftEage="238" RightEage="238" TopEage="55" BottomEage="55" Scale9OriginX="238" Scale9OriginY="55" Scale9Width="248" Scale9Height="59" ctype="ImageViewObjectData">
                    <Size X="724.0000" Y="169.0000" />
                    <Children>
                      <AbstractNodeData Name="fish_ui_fish_ui_icon0_2" ActionTag="2031608978" Tag="7673" RotationSkewX="180.0000" RotationSkewY="180.0000" IconVisible="False" LeftMargin="294.3789" RightMargin="297.6211" TopMargin="33.3513" BottomMargin="29.6487" ctype="SpriteObjectData">
                        <Size X="132.0000" Y="106.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="360.3789" Y="82.6487" />
                        <Scale ScaleX="1.3000" ScaleY="1.3000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4978" Y="0.4890" />
                        <PreSize X="0.1823" Y="0.6272" />
                        <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_icon0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="588.6508" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg1.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_1" ActionTag="1420488742" Tag="5406" IconVisible="True" PositionPercentXEnabled="True" TopMargin="1.0000" BottomMargin="-1.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_1" ActionTag="-1854127681" Tag="5408" IconVisible="False" LeftMargin="-500.0000" RightMargin="-500.0000" TopMargin="-620.0000" BottomMargin="-620.0000" TouchEnable="True" Scale9Enable="True" LeftEage="89" RightEage="93" TopEage="105" BottomEage="109" Scale9OriginX="89" Scale9OriginY="105" Scale9Width="205" Scale9Height="262" ctype="ImageViewObjectData">
                        <Size X="1000.0000" Y="1240.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="244" B="229" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Panel_3" Visible="False" ActionTag="-1536178186" VisibleForFrame="False" Tag="5409" IconVisible="False" LeftMargin="-500.0000" RightMargin="-500.0000" TopMargin="-620.0000" BottomMargin="-620.0000" TouchEnable="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                        <Size X="1000.0000" Y="1240.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <SingleColor A="255" R="150" G="200" B="255" />
                        <FirstColor A="255" R="150" G="200" B="255" />
                        <EndColor A="255" R="255" G="255" B="255" />
                        <ColorVector ScaleY="1.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="-1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Panel_teach" ActionTag="-1804961099" VisibleForFrame="False" Tag="727" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-540.0000" RightMargin="-540.0000" TopMargin="-1050.0000" BottomMargin="-1050.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="1080.0000" Y="2100.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
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
                  <AbstractNodeData Name="ListView_bg" ActionTag="323230182" Tag="17671" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-465.0000" RightMargin="-465.0000" TopMargin="-567.0000" BottomMargin="-585.0000" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" IsBounceEnabled="True" ScrollDirectionType="0" ItemMargin="-5" DirectionType="Vertical" HorizontalType="Align_HorizontalCenter" ctype="ListViewObjectData">
                    <Size X="930.0000" Y="1152.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-9.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <SingleColor A="255" R="150" G="150" B="255" />
                    <FirstColor A="255" R="150" G="150" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_close" ActionTag="-2120118098" Tag="17738" IconVisible="False" LeftMargin="434.0000" RightMargin="-538.0000" TopMargin="-642.0000" BottomMargin="512.0000" TouchEnable="True" FontSize="80" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="130.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="486.0000" Y="577.0000" />
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
                  <AbstractNodeData Name="FileNode_BagItem1" ActionTag="1815772597" VisibleForFrame="False" Tag="7461" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="ui/2020BagItem_1.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="885.0000" />
                <Scale ScaleX="0.7000" ScaleY="0.7000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.4320" Y="885.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5004" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_view_Changjing" ActionTag="-1288759255" Tag="2435" IconVisible="False" LeftMargin="-1320.8748" RightMargin="1470.8748" TopMargin="718.6528" BottomMargin="641.3472" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="930.0000" Y="410.0000" />
            <AnchorPoint />
            <Position X="-1320.8748" Y="641.3472" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-1.2230" Y="0.3623" />
            <PreSize X="0.8611" Y="0.2316" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="FileNode_1" ActionTag="-1680913855" Tag="19618" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" BottomMargin="1770.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="540.0000" Y="1770.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/2020Goldbanner.csd" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>