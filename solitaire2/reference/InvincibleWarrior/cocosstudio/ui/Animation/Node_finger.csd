<GameFile>
  <PropertyGroup Name="Node_finger" Type="Node" ID="d81d1d0d-01bd-47bf-8355-0534887141d2" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="81" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="-1659672869" Property="RotationSkew">
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
        <Timeline ActionTag="693490535" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-90.0000" Y="-90.0000">
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
        <Timeline ActionTag="693490535" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="81" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="50">
          <RenderColor A="255" R="233" G="150" B="122" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="16474" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="flash_undone0_1" ActionTag="693490535" Tag="16475" RotationSkewX="-90.0000" RotationSkewY="-90.0000" IconVisible="False" LeftMargin="12.6981" RightMargin="-75.6981" TopMargin="-43.6954" BottomMargin="-22.3046" ctype="SpriteObjectData">
            <Size X="63.0000" Y="66.0000" />
            <Children>
              <AbstractNodeData Name="ui_finger0_1" ActionTag="-1659672869" Tag="16476" IconVisible="False" LeftMargin="-13.0129" RightMargin="41.0129" TopMargin="-23.1049" BottomMargin="47.1049" ctype="SpriteObjectData">
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
            <AnchorPoint ScaleY="1.0000" />
            <Position X="12.6981" Y="43.6954" />
            <Scale ScaleX="2.1600" ScaleY="2.1600" />
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