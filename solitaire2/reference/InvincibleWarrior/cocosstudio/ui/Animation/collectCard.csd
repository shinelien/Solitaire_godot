<GameFile>
  <PropertyGroup Name="collectCard" Type="Node" ID="e09f82eb-0250-4b48-ba42-d3d557873872" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="76" Speed="1.0000" ActivedAnimationName="show">
        <Timeline ActionTag="2009225557" Property="Alpha">
          <IntFrame FrameIndex="15" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="30" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-2114802269" Property="Scale">
          <ScaleFrame FrameIndex="35" X="0.0001" Y="0.0001">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1113265354" Property="Scale">
          <ScaleFrame FrameIndex="20" X="0.0001" Y="0.0001">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1113265354" Property="Alpha">
          <IntFrame FrameIndex="19" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="20" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1043518912" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="75" Tween="False" Value="True" />
          <BoolFrame FrameIndex="76" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="show" StartIndex="0" EndIndex="76">
          <RenderColor A="255" R="255" G="250" B="250" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="216" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Node_5_0_0_0" ActionTag="-1300560074" Tag="217" IconVisible="True" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Level_win0_1" ActionTag="2009225557" Tag="218" IconVisible="False" LeftMargin="-45.0000" RightMargin="-45.0000" TopMargin="-61.5000" BottomMargin="-57.5000" ctype="SpriteObjectData">
                <Size X="90.0000" Y="119.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="2.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="Level_win0.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Level_win2_3" ActionTag="1113265354" Tag="219" IconVisible="False" LeftMargin="-4.9492" RightMargin="-51.0508" TopMargin="8.9363" BottomMargin="-64.9363" ctype="SpriteObjectData">
                <Size X="56.0000" Y="56.0000" />
                <Children>
                  <AbstractNodeData Name="Level_win3_4" ActionTag="-2114802269" Tag="220" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="11.5000" RightMargin="11.5000" TopMargin="14.5000" BottomMargin="14.5000" ctype="SpriteObjectData">
                    <Size X="33.0000" Y="27.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="28.0000" Y="28.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.5893" Y="0.4821" />
                    <FileData Type="PlistSubImage" Path="Level_win3.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="23.0508" Y="-36.9363" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="Level_win2.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Particle_3" ActionTag="-1043518912" Tag="221" IconVisible="True" LeftMargin="-5.0394" RightMargin="5.0394" TopMargin="-52.4957" BottomMargin="52.4957" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="-5.0394" Y="52.4957" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/start_0.plist" Plist="" />
                <BlendFunc Src="1" Dst="1" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>