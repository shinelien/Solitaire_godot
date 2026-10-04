<GameFile>
  <PropertyGroup Name="Likeme" Type="Layer" ID="23a32ab6-1dc2-4870-b072-b20e0759b1ce" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="95" Speed="1.0000">
        <Timeline ActionTag="-339198106" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="25" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-93734621" Property="ActionValue">
          <InnerActionFrame FrameIndex="0" Tween="False" InnerActionType="LoopAction" CurrentAniamtionName="KingLoop" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="987558575" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="6" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-836703918" Property="VisibleForFrame">
          <BoolFrame FrameIndex="2" Tween="False" Value="False" />
          <BoolFrame FrameIndex="10" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-836703918" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0001" Y="0.0001">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="2.3170" Y="2.3663">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="631432559" Property="RotationSkew">
          <ScaleFrame FrameIndex="10" X="5.0000" Y="4.9813">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="15.0000" Y="14.9813">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="26" X="15.0000" Y="14.9813">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="25.0000" Y="24.9813">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="6.0000" Y="5.9813">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="95" X="15.0000" Y="14.9813">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="205751870" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.9000" Y="0.9000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="205751870" Property="Alpha">
          <IntFrame FrameIndex="3" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="10" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="0" G="255" B="255" />
        </AnimationInfo>
        <AnimationInfo Name="loop" StartIndex="26" EndIndex="95">
          <RenderColor A="255" R="106" G="90" B="205" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="6792" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="-339198106" Alpha="0" Tag="7176" IconVisible="False" LeftMargin="0.0009" RightMargin="-0.0009" TopMargin="-779.9993" BottomMargin="-300.0007" TouchEnable="True" ClipAble="False" BackColorAlpha="127" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="3000.0000" />
            <AnchorPoint />
            <Position X="0.0009" Y="-300.0007" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" Y="-0.1563" />
            <PreSize X="1.0000" Y="1.5625" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_set" ActionTag="-1149567952" Tag="7174" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="0.0006" RightMargin="-0.0006" TopMargin="-0.5417" BottomMargin="0.5418" TouchEnable="True" ClipAble="False" BackColorAlpha="153" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Panel_out" ActionTag="-1345926153" Tag="7175" IconVisible="False" LeftMargin="-38.6321" RightMargin="-54.2830" TopMargin="-82.9064" BottomMargin="0.8423" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1172.9150" Y="2002.0641" />
                <AnchorPoint />
                <Position X="-38.6321" Y="0.8423" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.0358" Y="0.0004" />
                <PreSize X="1.0860" Y="1.0427" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="0.0006" Y="0.5418" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" Y="0.0003" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="173" G="216" B="230" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_2" ActionTag="205751870" Alpha="0" Tag="7098" IconVisible="True" PositionPercentXEnabled="True" VerticalEdge="TopEdge" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="859.0000" BottomMargin="1061.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="FileNode_1" Visible="False" ActionTag="-93734621" Tag="7177" IconVisible="True" LeftMargin="54.7996" RightMargin="-54.7996" TopMargin="-148.6100" BottomMargin="148.6100" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="54.7996" Y="148.6100" />
                <Scale ScaleX="1.3000" ScaleY="1.3000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="ui/Animation/Node_bag.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_1" ActionTag="-1140229317" Tag="7099" IconVisible="True" PositionPercentXEnabled="True" TopMargin="76.0000" BottomMargin="-76.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_7" ActionTag="987558575" Alpha="0" Tag="7100" IconVisible="False" LeftMargin="-470.3195" RightMargin="-470.3205" TopMargin="-304.0003" BottomMargin="-204.6196" Scale9Enable="True" LeftEage="70" RightEage="70" TopEage="70" BottomEage="134" Scale9OriginX="70" Scale9OriginY="70" Scale9Width="156" Scale9Height="201" ctype="ImageViewObjectData">
                    <Size X="940.6401" Y="508.6199" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position X="0.0005" Y="304.0003" />
                    <Scale ScaleX="1.0000" ScaleY="1.4000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="main_table1.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_1" ActionTag="382715699" Tag="7101" IconVisible="False" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="-300.0000" BottomMargin="-300.0000" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="90" BottomEage="90" Scale9OriginX="90" Scale9OriginY="90" Scale9Width="207" Scale9Height="296" ctype="ImageViewObjectData">
                    <Size X="800.0000" Y="600.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="244" B="229" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position Y="-76.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_close" ActionTag="155704171" Tag="7168" IconVisible="False" LeftMargin="332.4153" RightMargin="-436.4153" TopMargin="-254.4197" BottomMargin="124.4197" TouchEnable="True" FontSize="8" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="104.0000" Y="130.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="384.4153" Y="189.4197" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="255" G="255" B="255" />
                <DisabledFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                <PressedFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Particle_1" ActionTag="-836703918" VisibleForFrame="False" Tag="8453" IconVisible="True" LeftMargin="-9.1656" RightMargin="9.1656" TopMargin="-108.6575" BottomMargin="108.6575" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="-9.1656" Y="108.6575" />
                <Scale ScaleX="0.0001" ScaleY="0.0001" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                <BlendFunc Src="1" Dst="1" />
              </AbstractNodeData>
              <AbstractNodeData Name="UI_like_1" ActionTag="631432559" Tag="7285" RotationSkewX="5.0000" RotationSkewY="4.9813" IconVisible="False" LeftMargin="-76.8284" RightMargin="-84.1716" TopMargin="-196.2285" BottomMargin="-2.7715" ctype="SpriteObjectData">
                <Size X="161.0000" Y="199.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.3171" />
                <Position X="84.1716" Y="60.3314" />
                <Scale ScaleX="1.5100" ScaleY="1.5100" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="UI_like.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_title" ActionTag="-2022412607" Tag="7169" IconVisible="False" LeftMargin="-329.7857" RightMargin="-329.7812" TopMargin="-57.0461" BottomMargin="-171.0004" IsCustomSize="True" FontSize="50" LabelText="Ты очень сильный! веселый? пожалуйста, дайте нам положительную оценку." HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="659.5669" Y="228.0465" />
                <AnchorPoint ScaleX="0.5000" />
                <Position X="-0.0023" Y="-171.0004" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="48" G="34" B="23" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_yes" ActionTag="1813358306" Tag="7172" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-200.0000" RightMargin="-200.0000" TopMargin="194.0013" BottomMargin="-316.0013" TouchEnable="True" FontSize="14" LeftEage="110" RightEage="110" TopEage="32" BottomEage="32" Scale9OriginX="110" Scale9OriginY="32" Scale9Width="51" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="400.0000" Y="122.0000" />
                <Children>
                  <AbstractNodeData Name="Text_yes" ActionTag="-910623362" Tag="7173" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="168.5000" RightMargin="168.5000" TopMargin="37.5600" BottomMargin="42.4400" FontSize="42" LabelText="Yes" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="63.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="200.0000" Y="63.4400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5200" />
                    <PreSize X="0.1575" Y="0.3443" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="-255.0013" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="540.0000" Y="1061.0000" />
            <Scale ScaleX="0.9000" ScaleY="0.9000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5526" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>