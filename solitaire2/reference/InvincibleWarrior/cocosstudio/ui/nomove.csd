<GameFile>
  <PropertyGroup Name="nomove" Type="Layer" ID="b9fc7b35-c02b-4c83-81e3-b29819addfd5" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="15" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="1785220110" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-1960911587" Property="Position">
          <PointFrame FrameIndex="15" X="932.8990" Y="255.6531">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1366650963" Property="Scale">
          <ScaleFrame FrameIndex="15" X="0.8900" Y="0.8900">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-662901783" Property="Scale">
          <ScaleFrame FrameIndex="15" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-662901783" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="3" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-662901783" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="15" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="20">
          <RenderColor A="255" R="0" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="270" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="Panel_close" Visible="False" ActionTag="-988606714" Tag="3074" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_4" ActionTag="-662901783" VisibleForFrame="False" Alpha="0" Tag="649" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="204" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Image_1" ActionTag="-1366650963" Tag="12318" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="90.0000" RightMargin="90.0000" TopMargin="1238.2000" BottomMargin="431.8000" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="100" BottomEage="67" Scale9OriginX="90" Scale9OriginY="100" Scale9Width="116" Scale9Height="109" ctype="ImageViewObjectData">
                <Size X="900.0000" Y="250.0000" />
                <Children>
                  <AbstractNodeData Name="btn_use" ActionTag="-1842803808" Tag="681" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="602.5000" RightMargin="26.5000" TopMargin="64.0000" BottomMargin="64.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="271.0000" Y="122.0000" />
                    <Children>
                      <AbstractNodeData Name="Particle_1" ActionTag="1755164329" Tag="682" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="135.5000" RightMargin="135.5000" TopMargin="29.2800" BottomMargin="92.7200" ctype="ParticleObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="135.5000" Y="92.7200" />
                        <Scale ScaleX="1.4000" ScaleY="1.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.7600" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                        <BlendFunc Src="770" Dst="1" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_guankan" ActionTag="-1318447851" Tag="689" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="101.3400" RightMargin="79.6600" TopMargin="27.3400" BottomMargin="34.6600" FontSize="60" LabelText="Use" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="90.0000" Y="60.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="146.3400" Y="64.6600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5400" Y="0.5300" />
                        <PreSize X="0.3321" Y="0.4918" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Particle_1_0_0" ActionTag="1785220110" Tag="670" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="133.5488" RightMargin="137.4512" TopMargin="-3.9650" BottomMargin="125.9650" ctype="ParticleObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Navigate17_1_0" ActionTag="1738277685" Tag="668" RotationSkewX="50.0002" RotationSkewY="49.9994" IconVisible="False" LeftMargin="-127.1007" RightMargin="34.1007" TopMargin="-96.6220" BottomMargin="-83.3780" ctype="SpriteObjectData">
                            <Size X="93.0000" Y="180.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.1367" />
                            <Position X="-80.6007" Y="-58.7720" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="PlistSubImage" Path="Magic_0.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="133.5488" Y="125.9650" />
                        <Scale ScaleX="0.8000" ScaleY="0.8597" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4928" Y="1.0325" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                        <BlendFunc Src="1" Dst="1" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="738.0000" Y="125.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8200" Y="0.5000" />
                    <PreSize X="0.3011" Y="0.4880" />
                    <TextColor A="255" R="255" G="255" B="255" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_title" ActionTag="-614592453" VisibleForFrame="False" Tag="1254" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="262.5000" RightMargin="262.5000" TopMargin="57.5000" BottomMargin="142.5000" FontSize="50" LabelText="ARE YOU STUCK？" ShadowOffsetX="0.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="375.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="450.0000" Y="167.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.6700" />
                    <PreSize X="0.4167" Y="0.2000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="97" G="47" B="0" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_close" ActionTag="-1960911587" Tag="6791" IconVisible="False" LeftMargin="828.8990" RightMargin="-32.8990" TopMargin="-70.6531" BottomMargin="190.6531" TouchEnable="True" FontSize="8" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="130.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="932.8990" Y="255.6531" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.0366" Y="1.0226" />
                    <PreSize X="0.1156" Y="0.5200" />
                    <TextColor A="255" R="255" G="255" B="255" />
                    <DisabledFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_agian" ActionTag="-1080792577" Tag="671" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="26.5000" RightMargin="602.5000" TopMargin="64.0000" BottomMargin="64.0000" TouchEnable="True" FontSize="14" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="271.0000" Y="122.0000" />
                    <Children>
                      <AbstractNodeData Name="Particle_1" ActionTag="1648359948" Tag="672" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="135.5000" RightMargin="135.5000" TopMargin="29.2800" BottomMargin="92.7200" ctype="ParticleObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="135.5000" Y="92.7200" />
                        <Scale ScaleX="1.4000" ScaleY="1.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.7600" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                        <BlendFunc Src="770" Dst="1" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_guankan_0" ActionTag="-502519506" Tag="680" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="65.5000" RightMargin="65.5000" TopMargin="29.8400" BottomMargin="37.1600" FontSize="55" LabelText="Agian" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="140.0000" Y="55.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="135.5000" Y="64.6600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5300" />
                        <PreSize X="0.5166" Y="0.4508" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="162.0000" Y="125.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1800" Y="0.5000" />
                    <PreSize X="0.3011" Y="0.4880" />
                    <TextColor A="255" R="255" G="255" B="255" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_new game" ActionTag="-702979810" Tag="12312" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="314.7700" RightMargin="314.2300" TopMargin="64.0000" BottomMargin="64.0000" TouchEnable="True" FontSize="14" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="271.0000" Y="122.0000" />
                    <Children>
                      <AbstractNodeData Name="Particle_1" ActionTag="-754234031" Tag="12313" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="135.5000" RightMargin="135.5000" TopMargin="29.2800" BottomMargin="92.7200" ctype="ParticleObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="135.5000" Y="92.7200" />
                        <Scale ScaleX="1.4000" ScaleY="1.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.7600" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                        <BlendFunc Src="770" Dst="1" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_guankan_0" ActionTag="-1691481266" Tag="12314" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="23.5000" RightMargin="23.5000" TopMargin="29.8400" BottomMargin="37.1600" FontSize="55" LabelText="New game" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="224.0000" Y="55.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="135.5000" Y="64.6600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5300" />
                        <PreSize X="0.8266" Y="0.4508" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="450.2700" Y="125.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5003" Y="0.5000" />
                    <PreSize X="0.3011" Y="0.4880" />
                    <TextColor A="255" R="255" G="255" B="255" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.0000" Y="556.8000" />
                <Scale ScaleX="0.8900" ScaleY="0.8900" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2900" />
                <PreSize X="0.8333" Y="0.1302" />
                <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_shop2.png" Plist="ui1.plist" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="960.0000" />
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