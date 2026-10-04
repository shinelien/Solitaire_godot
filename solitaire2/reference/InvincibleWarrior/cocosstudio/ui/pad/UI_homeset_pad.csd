<GameFile>
  <PropertyGroup Name="UI_homeset_pad" Type="Layer" ID="7b65d462-dbe8-4c99-9f2a-9a08951449a4" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.6667" ActivedAnimationName="Start">
        <Timeline ActionTag="1052536986" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.2000" Y="0.2000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="2102939900" Property="Alpha">
          <IntFrame FrameIndex="1" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="12" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="255" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="273" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="panel_set" ActionTag="1050493431" Tag="51451" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="153" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Panel_out" ActionTag="2102939900" Alpha="0" Tag="51452" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="-0.0002" RightMargin="0.0002" TopMargin="0.0002" BottomMargin="-0.0003" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1080.0000" Y="1440.0000" />
                <Children>
                  <AbstractNodeData Name="Image_3" ActionTag="1052536986" Tag="51453" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="36.8050" RightMargin="489.1950" TopMargin="187.2000" BottomMargin="-7.2000" TouchEnable="True" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="66" BottomEage="113" Scale9OriginX="90" Scale9OriginY="66" Scale9Width="27" Scale9Height="34" ctype="ImageViewObjectData">
                    <Size X="554.0000" Y="1260.0000" />
                    <Children>
                      <AbstractNodeData Name="Ui_homeset0_149" ActionTag="311772611" Tag="51454" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="101.5800" RightMargin="356.4200" TopMargin="-58.0000" BottomMargin="1260.0000" ctype="SpriteObjectData">
                        <Size X="96.0000" Y="58.0000" />
                        <AnchorPoint ScaleX="0.5000" />
                        <Position X="149.5800" Y="1260.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.2700" Y="1.0000" />
                        <PreSize X="0.1733" Y="0.0460" />
                        <FileData Type="PlistSubImage" Path="Ui_homeset0.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_13" ActionTag="-1572648359" Tag="51455" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="277.0000" RightMargin="277.0000" BottomMargin="1260.0000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Button_info" ActionTag="1531093564" Tag="51456" IconVisible="False" LeftMargin="-200.0000" RightMargin="-200.0000" TopMargin="240.4987" BottomMargin="-390.4987" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="55" Scale9OriginY="39" Scale9Width="161" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_info" ActionTag="-1272625919" Tag="51457" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="75.0000" RightMargin="75.0000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="Statistics" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="250.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.6250" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position Y="-240.4987" />
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
                          <AbstractNodeData Name="Button_rank" ActionTag="724943655" Tag="51458" IconVisible="False" LeftMargin="-200.0001" RightMargin="-199.9999" TopMargin="430.3740" BottomMargin="-580.3740" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="55" Scale9OriginY="39" Scale9Width="161" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_rank" ActionTag="981521759" Tag="51459" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="112.5000" RightMargin="112.5000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="Ranking" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="175.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.4375" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="-0.0001" Y="-430.3740" />
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
                          <AbstractNodeData Name="Button_setting" ActionTag="1611103086" Tag="51460" IconVisible="False" LeftMargin="-199.9999" RightMargin="-200.0001" TopMargin="620.2493" BottomMargin="-770.2493" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="55" Scale9OriginY="39" Scale9Width="161" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_setting" ActionTag="-633114856" Tag="51461" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="112.5000" RightMargin="112.5000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="Setting" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="175.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.4375" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="img_new_Ver" ActionTag="-2105839429" Tag="4767" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="340.6998" RightMargin="-2.6998" TopMargin="-12.9715" BottomMargin="91.9715" LeftEage="11" RightEage="11" TopEage="10" BottomEage="10" Scale9OriginX="11" Scale9OriginY="10" Scale9Width="12" Scale9Height="19" ctype="ImageViewObjectData">
                                <Size X="62.0000" Y="71.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="371.6998" Y="127.4715" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.9292" Y="0.8498" />
                                <PreSize X="0.1550" Y="0.4733" />
                                <FileData Type="PlistSubImage" Path="main_tips1.png" Plist="ui1.plist" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="0.0001" Y="-620.2493" />
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
                          <AbstractNodeData Name="Button_fanKui" ActionTag="2147223905" Tag="51462" IconVisible="False" LeftMargin="-199.9999" RightMargin="-200.0001" TopMargin="999.9999" BottomMargin="-1149.9999" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="55" Scale9OriginY="39" Scale9Width="161" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_fanKui" ActionTag="1784819849" Tag="51463" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="150.0000" RightMargin="150.0000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="反馈" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="100.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.2500" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="0.0001" Y="-999.9999" />
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
                          <AbstractNodeData Name="Button_one" ActionTag="1077182706" Tag="51464" IconVisible="False" LeftMargin="-200.0000" RightMargin="-200.0000" TopMargin="50.6235" BottomMargin="-200.6235" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="55" Scale9OriginY="39" Scale9Width="161" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_one" ActionTag="-1320160686" Tag="51465" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="137.5000" RightMargin="137.5000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="Share" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="125.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.3125" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="img_new_lobby_share" ActionTag="848494" Tag="51466" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="31.4800" RightMargin="306.5200" TopMargin="12.8450" BottomMargin="66.1550" LeftEage="11" RightEage="11" TopEage="10" BottomEage="10" Scale9OriginX="11" Scale9OriginY="10" Scale9Width="12" Scale9Height="19" ctype="ImageViewObjectData">
                                <Size X="62.0000" Y="71.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="62.4800" Y="101.6550" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.1562" Y="0.6777" />
                                <PreSize X="0.1550" Y="0.4733" />
                                <FileData Type="PlistSubImage" Path="main_tips1.png" Plist="ui1.plist" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position Y="-50.6235" />
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
                          <AbstractNodeData Name="Button_share" ActionTag="2027464092" VisibleForFrame="False" Tag="51467" IconVisible="False" LeftMargin="-1151.5756" RightMargin="761.5756" TopMargin="885.3256" BottomMargin="-1065.3257" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="2" RightEage="2" TopEage="5" BottomEage="5" Scale9OriginX="2" Scale9OriginY="5" Scale9Width="42" Scale9Height="26" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="390.0000" Y="180.0000" />
                            <Children>
                              <AbstractNodeData Name="Ui_homeicon0_70" ActionTag="-549180536" Tag="51468" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="43.3000" RightMargin="300.7000" TopMargin="67.0000" BottomMargin="67.0000" ctype="SpriteObjectData">
                                <Size X="46.0000" Y="46.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="66.3000" Y="90.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.1700" Y="0.5000" />
                                <PreSize X="0.1179" Y="0.2556" />
                                <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                                <BlendFunc Src="1" Dst="771" />
                              </AbstractNodeData>
                              <AbstractNodeData Name="Text_share" ActionTag="882248058" Tag="51469" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="163.8000" RightMargin="131.2000" TopMargin="71.0000" BottomMargin="71.0000" FontSize="38" LabelText="Share" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="95.0000" Y="38.0000" />
                                <AnchorPoint ScaleY="0.5000" />
                                <Position X="163.8000" Y="90.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.4200" Y="0.5000" />
                                <PreSize X="0.2436" Y="0.2111" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleY="1.0000" />
                            <Position X="-1151.5756" Y="-885.3256" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Button_pingJia" ActionTag="79754890" VisibleForFrame="False" Tag="51470" IconVisible="False" LeftMargin="-1106.5314" RightMargin="706.5314" TopMargin="613.6002" BottomMargin="-763.6002" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="-9" Scale9OriginY="-3" Scale9Width="64" Scale9Height="42" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_pingJia" ActionTag="-1534374206" Tag="51471" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="168.0000" RightMargin="156.0000" TopMargin="56.0000" BottomMargin="56.0000" FontSize="38" LabelText="好评" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="76.0000" Y="38.0000" />
                                <AnchorPoint ScaleY="0.5000" />
                                <Position X="168.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.4200" Y="0.5000" />
                                <PreSize X="0.1900" Y="0.2533" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="-906.5314" Y="-613.6002" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Button_jiaoxue" ActionTag="294439272" Tag="51472" IconVisible="False" LeftMargin="-200.0000" RightMargin="-200.0000" TopMargin="810.1246" BottomMargin="-960.1246" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="55" Scale9OriginY="39" Scale9Width="161" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_jiaoxue" ActionTag="441787481" Tag="51473" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="150.0000" RightMargin="150.0000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="教学" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="100.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.2500" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position Y="-810.1246" />
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
                          <AbstractNodeData Name="Button_dingyue" ActionTag="893211407" VisibleForFrame="False" Tag="51474" IconVisible="False" LeftMargin="-192.3689" RightMargin="-207.6311" TopMargin="1192.5869" BottomMargin="-1342.5869" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="55" RightEage="55" TopEage="39" BottomEage="39" Scale9OriginX="-9" Scale9OriginY="-3" Scale9Width="64" Scale9Height="42" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="400.0000" Y="150.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_dingyue" ActionTag="1263108246" Tag="51475" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="150.0000" RightMargin="150.0000" TopMargin="50.0000" BottomMargin="50.0000" FontSize="50" LabelText="订阅" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                                <Size X="100.0000" Y="50.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="200.0000" Y="75.0000" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="0.5000" Y="0.5000" />
                                <PreSize X="0.2500" Y="0.3333" />
                                <OutlineColor A="255" R="255" G="0" B="0" />
                                <ShadowColor A="255" R="110" G="110" B="110" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="7.6311" Y="-1192.5869" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="277.0000" Y="1260.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="1.0000" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.1675" ScaleY="1.0000" />
                    <Position X="129.6000" Y="1252.8000" />
                    <Scale ScaleX="0.2000" ScaleY="0.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1200" Y="0.8700" />
                    <PreSize X="0.5130" Y="0.8750" />
                    <FileData Type="PlistSubImage" Path="Ui_homeset1.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_set_close" ActionTag="1476080438" Tag="51476" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-898.4858" RightMargin="1858.4858" TopMargin="997.1040" BottomMargin="322.8960" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="29" RightEage="29" TopEage="29" BottomEage="29" Scale9OriginX="-29" Scale9OriginY="-29" Scale9Width="58" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="120.0000" Y="120.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-838.4858" Y="382.8960" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-0.7764" Y="0.2659" />
                    <PreSize X="0.1111" Y="0.0833" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="-0.0002" Y="-0.0003" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="1.0000" Y="1.0000" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="255" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>