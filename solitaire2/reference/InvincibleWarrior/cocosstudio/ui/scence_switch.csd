<GameFile>
  <PropertyGroup Name="scence_switch" Type="Layer" ID="47a46594-7f06-43df-ac51-c25cc5f08996" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="160" Speed="1.0000" ActivedAnimationName="in">
        <Timeline ActionTag="-838301239" Property="VisibleForFrame">
          <BoolFrame FrameIndex="12" Tween="False" Value="False" />
          <BoolFrame FrameIndex="13" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="1546729305" Property="Position">
          <PointFrame FrameIndex="39" X="545.5852" Y="842.0338">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="540.0000" Y="965.9000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1546729305" Property="Alpha">
          <IntFrame FrameIndex="34" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="45" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="145" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="160" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-464240513" Property="Position">
          <PointFrame FrameIndex="34" X="543.7239" Y="922.7531">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="55" X="540.0000" Y="1196.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-464240513" Property="Alpha">
          <IntFrame FrameIndex="34" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="45" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="145" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="160" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="in" StartIndex="0" EndIndex="160">
          <RenderColor A="255" R="255" G="255" B="224" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="1381" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="2100.0000" />
        <Children>
          <AbstractNodeData Name="Panel_switch" ActionTag="616450248" Tag="1066" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="2100.0000" />
            <Children>
              <AbstractNodeData Name="Particle_1" ActionTag="-838301239" Tag="1382" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="1659.0000" BottomMargin="441.0000" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="540.0000" Y="441.0000" />
                <Scale ScaleX="1.5000" ScaleY="1.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2100" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/scenebubble.plist" Plist="" />
                <BlendFunc Src="1" Dst="1" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_3_0" ActionTag="1546729305" Alpha="231" Tag="1669" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="466.1567" RightMargin="463.8433" TopMargin="1117.2529" BottomMargin="897.7470" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="20" BottomEage="20" Scale9OriginX="64" Scale9OriginY="20" Scale9Width="67" Scale9Height="21" ctype="ImageViewObjectData">
                <Size X="150.0000" Y="85.0000" />
                <Children>
                  <AbstractNodeData Name="BitmapFontLabel_min" ActionTag="-1321756483" Tag="1670" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-29.6100" RightMargin="83.6100" TopMargin="13.4895" BottomMargin="-18.4895" LabelText="23" ctype="TextBMFontObjectData">
                    <Size X="96.0000" Y="90.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5138" />
                    <Position X="66.3900" Y="27.7525" />
                    <Scale ScaleX="0.4800" ScaleY="0.4800" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4426" Y="0.3265" />
                    <PreSize X="0.6400" Y="1.0588" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="BitmapFontLabel_1_0_0" ActionTag="317424017" Tag="1671" RotationSkewX="-68.4452" RotationSkewY="-68.4444" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="58.9850" RightMargin="59.0150" TopMargin="11.1170" BottomMargin="-16.1170" LabelText="-" ctype="TextBMFontObjectData">
                    <Size X="32.0000" Y="90.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="74.9850" Y="28.8830" />
                    <Scale ScaleX="1.3300" ScaleY="0.5500" />
                    <CColor A="255" R="0" G="255" B="0" />
                    <PrePosition X="0.4999" Y="0.3398" />
                    <PreSize X="0.2133" Y="1.0588" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="BitmapFontLabel_max" ActionTag="854779215" Tag="1672" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="95.1300" RightMargin="-40.1300" TopMargin="12.8425" BottomMargin="-17.8425" LabelText="25" ctype="TextBMFontObjectData">
                    <Size X="95.0000" Y="90.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="95.1300" Y="27.1575" />
                    <Scale ScaleX="0.4800" ScaleY="0.4800" />
                    <CColor A="255" R="0" G="255" B="0" />
                    <PrePosition X="0.6342" Y="0.3195" />
                    <PreSize X="0.6333" Y="1.0588" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="fish_ui_fish_ui_icon0_5_0" ActionTag="-662393100" Tag="1673" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="9.0000" RightMargin="9.0000" TopMargin="-44.5000" BottomMargin="23.5000" ctype="SpriteObjectData">
                    <Size X="132.0000" Y="106.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="75.0000" Y="76.5000" />
                    <Scale ScaleX="0.5900" ScaleY="0.5900" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.9000" />
                    <PreSize X="0.8800" Y="1.2471" />
                    <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_icon0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="541.1567" Y="940.2470" />
                <Scale ScaleX="1.2500" ScaleY="1.2500" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5011" Y="0.4477" />
                <PreSize X="0.1389" Y="0.0405" />
                <FileData Type="PlistSubImage" Path="fish_ui/fish_exp_1.png" Plist="ui1.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Challenge_chuangkoubg0_3" ActionTag="-464240513" Alpha="231" Tag="1689" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="339.7073" RightMargin="540.2927" TopMargin="822.0228" BottomMargin="1156.9772" ctype="SpriteObjectData">
                <Size X="200.0000" Y="121.0000" />
                <Children>
                  <AbstractNodeData Name="Challenge_chuangkoubg0_3_0" ActionTag="244263496" Tag="1690" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-2.0000" RightMargin="2.0000" ctype="SpriteObjectData">
                    <Size X="200.0000" Y="121.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="198.0000" Y="60.5000" />
                    <Scale ScaleX="-1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9900" Y="0.5000" />
                    <PreSize X="1.0000" Y="1.0000" />
                    <FileData Type="PlistSubImage" Path="Challenge_chuangkoubg0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="fish_Aquarium0_1_2" ActionTag="1009071484" Tag="1691" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="68.5000" RightMargin="-131.5000" TopMargin="-71.2100" BottomMargin="52.2100" ctype="SpriteObjectData">
                    <Size X="263.0000" Y="140.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="200.0000" Y="122.2100" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.0000" Y="1.0100" />
                    <PreSize X="1.3150" Y="1.1570" />
                    <FileData Type="PlistSubImage" Path="Logo0_1.png" Plist="Gamebox.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_Aquarium" ActionTag="-1055344104" Tag="1692" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="137.0000" RightMargin="-63.0000" TopMargin="116.9400" BottomMargin="-37.9400" FontSize="42" LabelText="海洋馆" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="126.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="200.0000" Y="-16.9400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.0000" Y="-0.1400" />
                    <PreSize X="0.6300" Y="0.3471" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="539.7073" Y="1217.4772" />
                <Scale ScaleX="1.2100" ScaleY="1.2100" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4997" Y="0.5798" />
                <PreSize X="0.1852" Y="0.0576" />
                <FileData Type="PlistSubImage" Path="Challenge_chuangkoubg0.png" Plist="ui.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
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
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>