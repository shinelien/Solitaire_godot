<GameFile>
  <PropertyGroup Name="Node_Npc" Type="Node" ID="563086cc-4a08-4692-b3ec-4df426f30893" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="90" Speed="1.0000" ActivedAnimationName="Npc_down">
        <Timeline ActionTag="1320354971" Property="FrameEvent">
          <EventFrame FrameIndex="0" Tween="False" Value="_1_0" />
          <EventFrame FrameIndex="10" Tween="False" Value="_1_1" />
          <EventFrame FrameIndex="20" Tween="False" Value="_1_2" />
          <EventFrame FrameIndex="30" Tween="False" Value="_1_3" />
          <EventFrame FrameIndex="40" Tween="False" Value="_1_0" />
          <EventFrame FrameIndex="50" Tween="False" Value="_0_0" />
          <EventFrame FrameIndex="60" Tween="False" Value="_0_1" />
          <EventFrame FrameIndex="70" Tween="False" Value="_0_2" />
          <EventFrame FrameIndex="80" Tween="False" Value="_0_3" />
          <EventFrame FrameIndex="90" Tween="False" Value="_0_0" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Npc_up" StartIndex="0" EndIndex="40">
          <RenderColor A="255" R="139" G="69" B="19" />
        </AnimationInfo>
        <AnimationInfo Name="Npc_down" StartIndex="50" EndIndex="90">
          <RenderColor A="255" R="255" G="105" B="180" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="109" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Sprite_1" ActionTag="1320354971" Tag="244" IconVisible="False" LeftMargin="-10.5000" RightMargin="-10.5000" TopMargin="-30.0000" ctype="SpriteObjectData">
            <Size X="21.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.9000" ScaleY="1.9000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="Human/gif/A_0_0.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>