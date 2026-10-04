<GameFile>
  <PropertyGroup Name="levelhint" Type="Node" ID="dc6b5c1b-0328-42ad-be71-28168a93915a" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="81" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="-2135088988" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="-20.0000" Y="-20.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="-20.0000" Y="-20.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1078253264" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-92.2917" Y="-92.2912">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="-102.0000" Y="-101.9994">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="-90.0000" Y="-89.9994">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="-102.0000" Y="-101.9994">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="-92.0000" Y="-91.9994">
            <EasingData Type="2" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1078253264" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="81" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="80">
          <RenderColor A="255" R="255" G="235" B="205" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="443" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Sprite_wait" ActionTag="-77478756" VisibleForFrame="False" Tag="1632" IconVisible="False" LeftMargin="-73.0000" RightMargin="-73.0000" TopMargin="-110.0000" BottomMargin="-110.0000" ctype="SpriteObjectData">
            <Size X="146.0000" Y="220.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="game_uibg3.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="flash_undone0_1" ActionTag="-1078253264" Tag="601" RotationSkewX="-92.0000" RotationSkewY="-91.9994" IconVisible="False" LeftMargin="39.1819" RightMargin="-102.1819" TopMargin="-158.4240" BottomMargin="92.4240" ctype="SpriteObjectData">
            <Size X="63.0000" Y="66.0000" />
            <Children>
              <AbstractNodeData Name="ui_finger0_1" ActionTag="-2135088988" Tag="602" IconVisible="False" LeftMargin="-13.0129" RightMargin="41.0129" TopMargin="-23.1049" BottomMargin="47.1049" ctype="SpriteObjectData">
                <Size X="35.0000" Y="42.0000" />
                <AnchorPoint ScaleX="0.7285" ScaleY="0.2052" />
                <Position X="12.4846" Y="55.7233" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1982" Y="0.8443" />
                <PreSize X="0.5556" Y="0.6364" />
                <FileData Type="PlistSubImage" Path="ui_finger0.png" Plist="ui.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.7290" ScaleY="0.2140" />
            <Position X="85.1089" Y="106.5480" />
            <Scale ScaleX="1.8000" ScaleY="1.8000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="ui_finger1.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>