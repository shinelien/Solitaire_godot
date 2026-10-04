<GameFile>
  <PropertyGroup Name="2020BagItem_1" Type="Node" ID="f1e87c56-eab4-4f3f-a2b7-c98009343cd1" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="15" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="1130448470" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.8000" Y="0.8000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1130448470" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="13" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="175" G="238" B="238" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="17706" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image_9" ActionTag="1130448470" Alpha="0" Tag="7663" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-450.0000" RightMargin="-450.0000" TopMargin="-575.0000" BottomMargin="-575.0000" Scale9Enable="True" LeftEage="101" RightEage="101" TopEage="101" BottomEage="101" Scale9OriginX="101" Scale9OriginY="101" Scale9Width="94" Scale9Height="74" ctype="ImageViewObjectData">
            <Size X="900.0000" Y="1150.0000" />
            <Children>
              <AbstractNodeData Name="ListView_card" ActionTag="989090172" Tag="7614" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="24.8900" RightMargin="30.1100" TopMargin="39.5000" BottomMargin="200.5000" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" IsBounceEnabled="True" ScrollDirectionType="0" DirectionType="Vertical" ctype="ListViewObjectData">
                <Size X="845.0000" Y="910.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="447.3900" Y="655.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4971" Y="0.5700" />
                <PreSize X="0.9389" Y="0.7913" />
                <SingleColor A="255" R="150" G="150" B="255" />
                <FirstColor A="255" R="150" G="150" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Image_2" ActionTag="928397684" Tag="6790" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="27.4700" RightMargin="462.5300" TopMargin="1009.1900" BottomMargin="64.8100" Scale9Enable="True" LeftEage="20" RightEage="31" TopEage="18" BottomEage="18" Scale9OriginX="20" Scale9OriginY="18" Scale9Width="16" Scale9Height="14" ctype="ImageViewObjectData">
                <Size X="410.0000" Y="76.0000" />
                <Children>
                  <AbstractNodeData Name="LoadingBar_card" ActionTag="-176103022" Tag="6791" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="5.0000" RightMargin="5.0000" TopMargin="5.5000" BottomMargin="5.5000" ProgressInfo="33" ctype="LoadingBarObjectData">
                    <Size X="400.0000" Y="65.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="205.0000" Y="38.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.9756" Y="0.8553" />
                    <ImageFileData Type="PlistSubImage" Path="ui_homelevel_0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_cardNum" ActionTag="-1289261502" Tag="7303" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="133.0000" RightMargin="133.0000" TopMargin="14.0000" BottomMargin="14.0000" FontSize="48" LabelText="0 / 52" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="144.0000" Y="48.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="205.0000" Y="38.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.3512" Y="0.6316" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="232.4700" Y="102.8100" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2583" Y="0.0894" />
                <PreSize X="0.4556" Y="0.0661" />
                <FileData Type="PlistSubImage" Path="ui_homelevel_3.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_3" ActionTag="841040020" Tag="7655" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="486.3522" RightMargin="27.5322" TopMargin="981.4450" BottomMargin="28.5550" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="57" RightEage="57" TopEage="11" BottomEage="11" Scale9OriginX="-57" Scale9OriginY="-11" Scale9Width="114" Scale9Height="22" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="386.1156" Y="140.0000" />
                <Children>
                  <AbstractNodeData Name="Text_19" ActionTag="-461359868" Tag="7656" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="143.0578" RightMargin="143.0578" TopMargin="45.0000" BottomMargin="45.0000" FontSize="50" LabelText="使用" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="100.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="193.0578" Y="70.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.2590" Y="0.3571" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="679.4100" Y="98.5550" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7549" Y="0.0857" />
                <PreSize X="0.4290" Y="0.1217" />
                <TextColor A="255" R="65" G="65" B="70" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_card_item1_get" ActionTag="984019328" Tag="8286" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="503.9100" RightMargin="45.0900" TopMargin="990.4450" BottomMargin="37.5550" TouchEnable="True" FontSize="14" LeftEage="57" RightEage="57" TopEage="11" BottomEage="11" Scale9OriginX="57" Scale9OriginY="11" Scale9Width="157" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="351.0000" Y="122.0000" />
                <Children>
                  <AbstractNodeData Name="Text_card_item1_get" ActionTag="-1151597339" Tag="8287" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="125.5000" RightMargin="125.5000" TopMargin="36.0000" BottomMargin="36.0000" FontSize="50" LabelText="使用" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="100.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="175.5000" Y="61.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.2849" Y="0.4098" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="679.4100" Y="98.5550" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7549" Y="0.0857" />
                <PreSize X="0.3900" Y="0.1061" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_card_item1_close" ActionTag="-1769880558" Tag="7662" IconVisible="False" LeftMargin="828.8628" RightMargin="-32.8628" TopMargin="-22.7404" BottomMargin="1042.7404" TouchEnable="True" FontSize="72" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="104.0000" Y="130.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="880.8628" Y="1107.7404" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9787" Y="0.9633" />
                <PreSize X="0.1156" Y="0.1130" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                <PressedFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="0.8000" ScaleY="0.8000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_shop1.png" Plist="ui1.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_card" ActionTag="613593884" Tag="8051" IconVisible="False" LeftMargin="-437.3529" RightMargin="-407.6471" TopMargin="1289.2920" BottomMargin="-1589.2920" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="845.0000" Y="300.0000" />
            <Children>
              <AbstractNodeData Name="img_card" ActionTag="-281838344" Tag="6326" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="348.5000" RightMargin="348.5000" TopMargin="40.0000" BottomMargin="40.0000" ctype="SpriteObjectData">
                <Size X="148.0000" Y="220.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="422.5000" Y="150.0000" />
                <Scale ScaleX="1.0000" ScaleY="0.9900" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.1751" Y="0.7333" />
                <FileData Type="Normal" Path="card_0_1_0.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="img_card_0" ActionTag="-1557657083" Tag="8052" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="10.5000" RightMargin="686.5000" TopMargin="40.0000" BottomMargin="40.0000" ctype="SpriteObjectData">
                <Size X="148.0000" Y="220.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="84.5000" Y="150.0000" />
                <Scale ScaleX="1.0000" ScaleY="0.9900" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1000" Y="0.5000" />
                <PreSize X="0.1751" Y="0.7333" />
                <FileData Type="Normal" Path="card_0_1_0.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="img_card_1" ActionTag="690253038" Tag="8053" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="179.5000" RightMargin="517.5000" TopMargin="40.0000" BottomMargin="40.0000" ctype="SpriteObjectData">
                <Size X="148.0000" Y="220.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="253.5000" Y="150.0000" />
                <Scale ScaleX="1.0000" ScaleY="0.9900" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3000" Y="0.5000" />
                <PreSize X="0.1751" Y="0.7333" />
                <FileData Type="Normal" Path="card_0_1_0.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="img_card_2" ActionTag="-1942204481" Tag="8054" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="517.5000" RightMargin="179.5000" TopMargin="40.0000" BottomMargin="40.0000" ctype="SpriteObjectData">
                <Size X="148.0000" Y="220.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="591.5000" Y="150.0000" />
                <Scale ScaleX="1.0000" ScaleY="0.9900" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7000" Y="0.5000" />
                <PreSize X="0.1751" Y="0.7333" />
                <FileData Type="Normal" Path="card_0_1_0.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="img_card_3" ActionTag="-1805697699" Tag="8055" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="686.5000" RightMargin="10.5000" TopMargin="40.0000" BottomMargin="40.0000" ctype="SpriteObjectData">
                <Size X="148.0000" Y="220.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="760.5000" Y="150.0000" />
                <Scale ScaleX="1.0000" ScaleY="0.9900" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9000" Y="0.5000" />
                <PreSize X="0.1751" Y="0.7333" />
                <FileData Type="Normal" Path="card_0_1_0.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-437.3529" Y="-1589.2920" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
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