<GameFile>
  <PropertyGroup Name="CoinLayer_pad" Type="Layer" ID="09bf9f40-d007-43da-aacc-e448cf996178" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="50" Speed="1.0000" ActivedAnimationName="loop">
        <Timeline ActionTag="520657775" Property="Alpha">
          <IntFrame FrameIndex="0" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="26" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1505906630" Property="Scale">
          <ScaleFrame FrameIndex="25" X="1.0000" Y="0.0001">
            <EasingData Type="21" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1461690378" Property="VisibleForFrame">
          <BoolFrame FrameIndex="34" Tween="False" Value="False" />
          <BoolFrame FrameIndex="35" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-340520691" Property="Scale">
          <ScaleFrame FrameIndex="25" X="1.0000" Y="0.6000">
            <EasingData Type="4" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="422843479" Property="Position">
          <PointFrame FrameIndex="25" X="0.9998" Y="21.0000">
            <EasingData Type="21" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="1.7518" Y="237.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="422843479" Property="Scale">
          <ScaleFrame FrameIndex="25" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.9300" Y="0.0001">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-290445469" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.4000" Y="0.4000">
            <EasingData Type="23" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="loop" StartIndex="0" EndIndex="1000">
          <RenderColor A="255" R="139" G="69" B="19" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="111" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_close" ActionTag="520657775" Tag="557" IconVisible="False" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_coin" ActionTag="1653207918" Tag="117" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="250.0000" RightMargin="250.0000" TopMargin="310.0000" BottomMargin="310.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="580.0000" Y="820.0000" />
            <Children>
              <AbstractNodeData Name="Node_3" ActionTag="386422829" Tag="537" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="290.0000" RightMargin="290.0000" TopMargin="410.0000" BottomMargin="410.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_1" ActionTag="448114600" Tag="538" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-430.0000" TopMargin="-600.0000" BottomMargin="-600.0000" Scale9Enable="True" LeftEage="113" RightEage="113" TopEage="270" BottomEage="270" Scale9OriginX="113" Scale9OriginY="270" Scale9Width="117" Scale9Height="102" ctype="ImageViewObjectData">
                    <Size X="430.0000" Y="1200.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_1_0" ActionTag="-1038205556" Tag="539" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" FlipX="True" Scale9Enable="True" LeftEage="113" RightEage="113" TopEage="270" BottomEage="270" Scale9OriginX="113" Scale9OriginY="270" Scale9Width="117" Scale9Height="102" ctype="ImageViewObjectData">
                        <Size X="430.0000" Y="1200.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="430.0000" Y="600.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="ui_giftbg0.png" Plist="ui.plist" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_giftbg0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_2" ActionTag="-290445469" Tag="542" IconVisible="True" PositionPercentXEnabled="True" TopMargin="-257.0000" BottomMargin="257.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="ui_gift3_4" ActionTag="2012328197" Tag="543" IconVisible="False" LeftMargin="-168.7296" RightMargin="-169.2704" BottomMargin="-36.0000" ctype="SpriteObjectData">
                        <Size X="338.0000" Y="36.0000" />
                        <Children>
                          <AbstractNodeData Name="ui_gift1_2" ActionTag="1505906630" Tag="544" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-18.0000" RightMargin="-18.0000" TopMargin="-249.0002" BottomMargin="35.0002" ctype="SpriteObjectData">
                            <Size X="374.0000" Y="250.0000" />
                            <AnchorPoint ScaleX="0.5000" />
                            <Position X="169.0000" Y="35.0002" />
                            <Scale ScaleX="1.0000" ScaleY="0.0001" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.9722" />
                            <PreSize X="1.1065" Y="6.9444" />
                            <FileData Type="PlistSubImage" Path="ui_gift1.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Particle_1_0" ActionTag="1461690378" VisibleForFrame="False" Tag="545" IconVisible="True" PositionPercentXEnabled="True" LeftMargin="162.5780" RightMargin="175.4220" TopMargin="-2.5856" BottomMargin="38.5856" ctype="ParticleObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="162.5780" Y="38.5856" />
                            <Scale ScaleX="2.3792" ScaleY="1.7704" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.4810" Y="1.0718" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                            <BlendFunc Src="1" Dst="1" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="ui_gift2_3" ActionTag="601239792" Tag="546" IconVisible="False" LeftMargin="-29.0000" RightMargin="-33.0000" TopMargin="-0.5000" BottomMargin="-118.5000" ctype="SpriteObjectData">
                            <Size X="400.0000" Y="155.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="171.0000" Y="-41.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5059" Y="-1.1389" />
                            <PreSize X="1.1834" Y="4.3056" />
                            <FileData Type="PlistSubImage" Path="ui_gift2.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="ui_gift4_5" ActionTag="-340520691" Tag="547" IconVisible="False" LeftMargin="-16.0000" RightMargin="-16.0000" TopMargin="-35.0705" BottomMargin="-18.9295" ctype="SpriteObjectData">
                            <Size X="370.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" />
                            <Position X="169.0000" Y="-18.9295" />
                            <Scale ScaleX="1.0000" ScaleY="0.6000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="-0.5258" />
                            <PreSize X="1.0947" Y="2.5000" />
                            <FileData Type="PlistSubImage" Path="ui_gift4.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.4992" ScaleY="1.0000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="ui_gift3.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="ui_gift0_1" ActionTag="422843479" Tag="548" IconVisible="False" LeftMargin="-199.7602" RightMargin="-200.2398" TopMargin="-21.0000" BottomMargin="-55.0000" ctype="SpriteObjectData">
                        <Size X="400.0000" Y="76.0000" />
                        <AnchorPoint ScaleX="0.5019" ScaleY="1.0000" />
                        <Position X="0.9998" Y="21.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="ui_gift0.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="257.0000" />
                    <Scale ScaleX="0.4000" ScaleY="0.4000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Particle_10_0" ActionTag="-681994333" Tag="1382" IconVisible="True" LeftMargin="83.5612" RightMargin="-83.5612" TopMargin="-334.2400" BottomMargin="334.2400" ctype="ParticleObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="83.5612" Y="334.2400" />
                    <Scale ScaleX="0.2000" ScaleY="0.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Particicle/over.plist" Plist="" />
                    <BlendFunc Src="1" Dst="1" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Particle_10" ActionTag="-198330920" Tag="1381" IconVisible="True" LeftMargin="-72.9872" RightMargin="72.9872" TopMargin="-344.5483" BottomMargin="344.5483" ctype="ParticleObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="-72.9872" Y="344.5483" />
                    <Scale ScaleX="-0.2000" ScaleY="0.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Particicle/over.plist" Plist="" />
                    <BlendFunc Src="1" Dst="1" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_coin_close" ActionTag="-71016835" Tag="122" IconVisible="False" LeftMargin="320.0000" RightMargin="-440.0000" TopMargin="-616.9999" BottomMargin="496.9999" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="29" RightEage="29" TopEage="11" BottomEage="11" Scale9OriginX="29" Scale9OriginY="11" Scale9Width="62" Scale9Height="98" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="120.0000" Y="120.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="380.0000" Y="556.9999" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_btn_close3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_btn_close2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="panel_ads" ActionTag="-1511157496" Tag="123" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-378.0000" RightMargin="-378.0000" TopMargin="86.9998" BottomMargin="-224.9998" Scale9Enable="True" LeftEage="20" RightEage="20" TopEage="30" BottomEage="30" Scale9OriginX="20" Scale9OriginY="30" Scale9Width="38" Scale9Height="96" ctype="ImageViewObjectData">
                    <Size X="756.0000" Y="138.0000" />
                    <Children>
                      <AbstractNodeData Name="btn_ads" ActionTag="-394161642" Tag="125" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="534.0400" RightMargin="19.9600" TopMargin="11.2400" BottomMargin="16.7600" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="100" RightEage="100" TopEage="35" BottomEage="35" Scale9OriginX="100" Scale9OriginY="35" Scale9Width="71" Scale9Height="52" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="202.0000" Y="110.0000" />
                        <Children>
                          <AbstractNodeData Name="text_ads" ActionTag="201097381" Tag="147" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="71.0000" RightMargin="71.0000" TopMargin="35.8000" BottomMargin="40.2000" FontSize="30" LabelText="领取" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="60.0000" Y="34.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="101.0000" Y="57.2000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5200" />
                            <PreSize X="0.2970" Y="0.3091" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Particle_1" ActionTag="993097839" Tag="6381" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="98.5962" RightMargin="103.4038" TopMargin="40.3590" BottomMargin="69.6410" ctype="ParticleObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="98.5962" Y="69.6410" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.4881" Y="0.6331" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                            <BlendFunc Src="770" Dst="1" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="635.0400" Y="71.7600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8400" Y="0.5200" />
                        <PreSize X="0.2672" Y="0.7971" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_14" ActionTag="232949723" Tag="124" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="21.1120" RightMargin="622.8880" TopMargin="7.0246" BottomMargin="18.9754" LeftEage="27" RightEage="27" TopEage="29" BottomEage="29" Scale9OriginX="27" Scale9OriginY="29" Scale9Width="58" Scale9Height="54" ctype="ImageViewObjectData">
                        <Size X="112.0000" Y="112.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="77.1120" Y="74.9754" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="0" G="255" B="80" />
                        <PrePosition X="0.1020" Y="0.5433" />
                        <PreSize X="0.1481" Y="0.8116" />
                        <FileData Type="PlistSubImage" Path="btn1_ad0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_three" ActionTag="1470613877" Tag="126" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="298.0000" RightMargin="298.0000" TopMargin="-47.3400" BottomMargin="140.3400" FontSize="40" LabelText="领取双倍" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="378.0000" Y="162.8400" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="76" G="49" B="0" />
                        <PrePosition X="0.5000" Y="1.1800" />
                        <PreSize X="0.2116" Y="0.3261" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_18" ActionTag="-1104356990" Tag="144" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="188.8139" RightMargin="434.0547" TopMargin="-0.7003" BottomMargin="1.2040" LeftEage="20" RightEage="20" TopEage="20" BottomEage="20" Scale9OriginX="20" Scale9OriginY="20" Scale9Width="21" Scale9Height="23" ctype="ImageViewObjectData">
                        <Size X="133.1313" Y="137.4963" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="255.3796" Y="69.9522" />
                        <Scale ScaleX="0.3800" ScaleY="0.3800" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.3378" Y="0.5069" />
                        <PreSize X="0.1761" Y="0.9964" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_three_des" ActionTag="1171124905" Tag="127" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="293.3200" RightMargin="338.6800" TopMargin="37.5000" BottomMargin="37.5000" FontSize="55" LabelText="+500" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="124.0000" Y="63.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="355.3200" Y="69.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4700" Y="0.5000" />
                        <PreSize X="0.1640" Y="0.4565" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-155.9998" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="panel_freecoin" ActionTag="-1964821494" Tag="128" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-378.0000" RightMargin="-378.0000" TopMargin="301.9995" BottomMargin="-439.9995" Scale9Enable="True" LeftEage="20" RightEage="20" TopEage="30" BottomEage="30" Scale9OriginX="20" Scale9OriginY="30" Scale9Width="38" Scale9Height="96" ctype="ImageViewObjectData">
                    <Size X="756.0000" Y="138.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_14" ActionTag="-690056447" Tag="129" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="39.6000" RightMargin="644.4000" TopMargin="21.3600" BottomMargin="29.6400" LeftEage="27" RightEage="27" TopEage="29" BottomEage="29" Scale9OriginX="27" Scale9OriginY="29" Scale9Width="18" Scale9Height="29" ctype="ImageViewObjectData">
                        <Size X="72.0000" Y="87.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="75.6000" Y="73.1400" />
                        <Scale ScaleX="0.9000" ScaleY="0.9000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1000" Y="0.5300" />
                        <PreSize X="0.0952" Y="0.6304" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_left" ActionTag="-1246847358" Tag="131" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="298.0000" RightMargin="298.0000" TopMargin="-47.3400" BottomMargin="140.3400" FontSize="40" LabelText="免费领取" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="378.0000" Y="162.8400" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="76" G="49" B="0" />
                        <PrePosition X="0.5000" Y="1.1800" />
                        <PreSize X="0.2116" Y="0.3261" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_18_0" ActionTag="1957247604" Tag="145" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="180.3975" RightMargin="424.9160" TopMargin="-7.9006" BottomMargin="-9.7264" LeftEage="20" RightEage="20" TopEage="20" BottomEage="20" Scale9OriginX="20" Scale9OriginY="20" Scale9Width="21" Scale9Height="23" ctype="ImageViewObjectData">
                        <Size X="150.6865" Y="155.6270" />
                        <AnchorPoint ScaleX="0.4822" ScaleY="0.5009" />
                        <Position X="253.0585" Y="68.2272" />
                        <Scale ScaleX="0.3800" ScaleY="0.3800" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.3347" Y="0.4944" />
                        <PreSize X="0.1993" Y="1.1277" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_three_des1" ActionTag="-1721803197" Tag="146" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="293.3200" RightMargin="338.6800" TopMargin="37.5000" BottomMargin="37.5000" FontSize="55" LabelText="+500" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="124.0000" Y="63.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="355.3200" Y="69.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4700" Y="0.5000" />
                        <PreSize X="0.1640" Y="0.4565" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_freecoin" ActionTag="1293101110" Tag="149" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="534.0400" RightMargin="19.9600" TopMargin="11.2400" BottomMargin="16.7600" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="100" RightEage="100" TopEage="35" BottomEage="35" Scale9OriginX="100" Scale9OriginY="35" Scale9Width="71" Scale9Height="52" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="202.0000" Y="110.0000" />
                        <Children>
                          <AbstractNodeData Name="text_freecoin" ActionTag="-1209157902" Tag="150" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="71.0000" RightMargin="71.0000" TopMargin="35.8000" BottomMargin="40.2000" FontSize="30" LabelText="领取" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="60.0000" Y="34.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="101.0000" Y="57.2000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5200" />
                            <PreSize X="0.2970" Y="0.3091" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="635.0400" Y="71.7600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8400" Y="0.5200" />
                        <PreSize X="0.2672" Y="0.7971" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_free" ActionTag="899206634" VisibleForFrame="False" Tag="89" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="537.2400" RightMargin="98.7600" TopMargin="28.5400" BottomMargin="75.4600" FontSize="30" LabelText="免费领奖" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="120.0000" Y="34.0000" />
                        <Children>
                          <AbstractNodeData Name="atlasLabel_time" ActionTag="510555139" Tag="91" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.5980" RightMargin="30.4020" TopMargin="45.3220" BottomMargin="-31.3220" CharWidth="12" CharHeight="20" LabelText="00/00" StartChar="." ctype="TextAtlasObjectData">
                            <Size X="60.0000" Y="20.0000" />
                            <AnchorPoint ScaleX="0.5067" ScaleY="0.5325" />
                            <Position X="60.0000" Y="-20.6720" />
                            <Scale ScaleX="1.5000" ScaleY="1.5000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="-0.6080" />
                            <PreSize X="0.5000" Y="0.5882" />
                            <LabelAtlasFileImage_CNB Type="Normal" Path="" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="597.2400" Y="92.4600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.7900" Y="0.6700" />
                        <PreSize X="0.1587" Y="0.2464" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-370.9995" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_7" ActionTag="-1426089876" Tag="143" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-284.5000" RightMargin="-284.5000" TopMargin="-85.5000" BottomMargin="28.5000" FontSize="50" LabelText="الحصول على العملات الذهبية مجانا" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="569.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="57.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="76" G="49" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg4_1_0_0_0" ActionTag="1411622767" Tag="556" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-283.0000" RightMargin="-283.0000" TopMargin="-33.0000" BottomMargin="-7.0000" ctype="SpriteObjectData">
                    <Size X="566.0000" Y="40.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="13.0000" />
                    <Scale ScaleX="1.1400" ScaleY="0.9000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg4.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="290.0000" Y="410.0000" />
                <Scale ScaleX="0.7000" ScaleY="0.7000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="720.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.5370" Y="0.5694" />
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