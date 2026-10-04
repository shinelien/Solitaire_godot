<GameFile>
  <PropertyGroup Name="Magic" Type="Node" ID="06f0c005-4d14-4246-9dd6-821ed2bd0b5d" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="113" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="1809321041" Property="Scale">
          <ScaleFrame FrameIndex="94" X="2.0000" Y="2.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="110" X="0.0010" Y="0.0010">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1809321041" Property="VisibleForFrame">
          <BoolFrame FrameIndex="110" Tween="False" Value="True" />
          <BoolFrame FrameIndex="113" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-1161311193" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0010" Y="0.0010">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="33" X="2.0000" Y="2.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="2.0000" Y="2.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1161311193" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="9" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="-20.0000" Y="100.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="55" X="-20.0000" Y="100.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1161311193" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="44.0000" Y="43.9997">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="37.0000" Y="36.9997">
            <EasingData Type="21" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="115.8914" Y="115.8911">
            <EasingData Type="21" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="52.7783" Y="52.7780">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="65" X="37.0000" Y="36.9997">
            <EasingData Type="21" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1161311193" Property="Alpha">
          <IntFrame FrameIndex="55" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="88" Value="255">
            <EasingData Type="7" />
          </IntFrame>
          <IntFrame FrameIndex="109" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1161311193" Property="FrameEvent">
          <EventFrame FrameIndex="55" Tween="False" Value="magic" />
        </Timeline>
        <Timeline ActionTag="1986253422" Property="VisibleForFrame">
          <BoolFrame FrameIndex="2" Tween="False" Value="False" />
          <BoolFrame FrameIndex="10" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="113">
          <RenderColor A="255" R="255" G="239" B="213" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="535" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Magic_0_1" ActionTag="-1161311193" UserData="0" Tag="536" RotationSkewX="73.0057" RotationSkewY="73.0054" IconVisible="False" LeftMargin="-66.3140" RightMargin="-26.6860" TopMargin="-244.0000" BottomMargin="64.0000" ctype="SpriteObjectData">
            <Size X="93.0000" Y="180.0000" />
            <Children>
              <AbstractNodeData Name="Particle_4" ActionTag="1809321041" Tag="1737" IconVisible="True" LeftMargin="47.3240" RightMargin="45.6760" TopMargin="52.0028" BottomMargin="127.9972" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="47.3240" Y="127.9972" />
                <Scale ScaleX="2.0000" ScaleY="2.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5089" Y="0.7111" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Default" Path="Default/defaultParticle.plist" Plist="" />
                <BlendFunc Src="775" Dst="1" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.4980" ScaleY="0.2000" />
            <Position X="-20.0000" Y="100.0000" />
            <Scale ScaleX="2.0000" ScaleY="2.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="Magic_0.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Particle_5" ActionTag="1986253422" Tag="1738" IconVisible="True" LeftMargin="38.2458" RightMargin="-38.2458" TopMargin="-33.8874" BottomMargin="33.8874" ctype="ParticleObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="38.2458" Y="33.8874" />
            <Scale ScaleX="2.3000" ScaleY="2.3000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Particicle/Magic0.plist" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>