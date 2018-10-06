<map version="freeplane 1.3.0">
<!--To view this file, download free mind mapping software Freeplane from http://freeplane.sourceforge.net -->
<node TEXT="Chat" ID="ID_1723255651" CREATED="1283093380553" MODIFIED="1538810310019"><hook NAME="MapStyle">

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node">
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right">
<stylenode LOCALIZED_TEXT="default" MAX_WIDTH="600" COLOR="#000000" STYLE="as_parent">
<font NAME="SansSerif" SIZE="10" BOLD="false" ITALIC="false"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.note"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important">
<icon BUILTIN="yes"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#0033ff">
<font SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#00b439">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#990000">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#111111">
<font SIZE="10"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="9"/>
<hook NAME="FirstGroupNode"/>
<node TEXT="Udp_Part" POSITION="right" ID="ID_1857210656" CREATED="1538809415825" MODIFIED="1538811753022">
<edge COLOR="#0000ff"/>
<node TEXT="ClientTag" ID="ID_1591997086" CREATED="1538810334006" MODIFIED="1538811753022" HGAP="10" VSHIFT="-40">
<node TEXT="userName:String" ID="ID_339017543" CREATED="1538810709058" MODIFIED="1538810814089"/>
<node TEXT="ipAddress:String" ID="ID_322738134" CREATED="1538810814636" MODIFIED="1538810829523"/>
<node TEXT="time(&#x432;&#x440;&#x435;&#x43c;&#x44f; &#x43f;&#x43e;&#x441;&#x43b;&#x435;&#x434;&#x43d;&#x435;&#x433;&#x43e; &#x43e;&#x442;&#x43a;&#x43b;&#x438;&#x43a;&#x430;):String" ID="ID_519725478" CREATED="1538810830300" MODIFIED="1538810850535"/>
<node TEXT="port:int" ID="ID_1453434025" CREATED="1538810850936" MODIFIED="1538810884984"/>
<node TEXT="uid:String" ID="ID_588570558" CREATED="1538810885415" MODIFIED="1538810899884"/>
</node>
<node TEXT="Server" ID="ID_148744882" CREATED="1538810457994" MODIFIED="1538811750186" VSHIFT="-40">
<node TEXT="udpServSocketList: QList&lt;QUdpSocket*&gt;" ID="ID_1527217068" CREATED="1538811317615" MODIFIED="1538811433133"/>
<node TEXT="*clientList: ClientList" ID="ID_1104935018" CREATED="1538811433622" MODIFIED="1538811460595"/>
<node TEXT="processPendingDatagrams() (&#x437;&#x430;&#x43f;&#x43e;&#x43b;&#x43d;&#x44f;&#x435;&#x442;&#x441;&#x44f; Tag &#x438; &#x434;&#x43e;&#x431;&#x430;&#x432;&#x43b;&#x44f;&#x435;&#x442;&#x441;&#x44f; &#x432; &#x441;&#x43f;&#x438;&#x441;&#x43e;&#x43a; &#x442;&#x435;&#x433;&#x43e;&#x432;): void" ID="ID_179681664" CREATED="1538811461115" MODIFIED="1538811513884"/>
</node>
<node TEXT="Client" ID="ID_1497678354" CREATED="1538810471647" MODIFIED="1538811742556" HGAP="30" VSHIFT="90">
<node TEXT="*id: IdGenerator" ID="ID_401912350" CREATED="1538810481098" MODIFIED="1538811559994"/>
<node TEXT="*timer: QTimer" ID="ID_704280638" CREATED="1538811560511" MODIFIED="1538811736200" VSHIFT="30"/>
<node TEXT="udpSocketList: QList&lt;QUdpSocket*&gt;" ID="ID_1053483674" CREATED="1538811579195" MODIFIED="1538811601197"/>
<node TEXT="addressList: QList&lt;QHostAddress&gt;" ID="ID_1264947591" CREATED="1538811601663" MODIFIED="1538811623562"/>
<node TEXT="sendDatagram(): void" ID="ID_710646509" CREATED="1538811623826" MODIFIED="1538811642700"/>
</node>
<node TEXT="IdGenerator" ID="ID_1618674873" CREATED="1538810493448" MODIFIED="1538811717742" VSHIFT="110">
<node TEXT="genId() (&#x433;&#x435;&#x43d;&#x435;&#x440;&#x438;&#x440;&#x443;&#x435;&#x43c; &#x443;&#x43d;&#x438;&#x43a;&#x430;&#x43b;&#x44c;&#x43d;&#x44b;&#x439; &#x430;&#x439;&#x434;&#x438;&#x448;&#x43d;&#x438;&#x43a;): String" ID="ID_1316194879" CREATED="1538811646230" MODIFIED="1538811707296"/>
</node>
<node TEXT="ClientList" ID="ID_1675410348" CREATED="1538810914535" MODIFIED="1538811728335" VSHIFT="60">
<node TEXT="list: QList&lt;ClientTag*&gt;" ID="ID_1877077854" CREATED="1538811138541" MODIFIED="1538811190485"/>
<node TEXT="slotNewClientTag(ClientTag* client):void" ID="ID_1037617907" CREATED="1538811195554" MODIFIED="1538811222663"/>
<node TEXT="printClientList(): QStringList" ID="ID_480572472" CREATED="1538811223101" MODIFIED="1538811241583"/>
<node TEXT="refreshList() (&#x43f;&#x440;&#x43e;&#x432;&#x435;&#x440;&#x43a;&#x430; &#x43a;&#x43b;&#x438;&#x435;&#x43d;&#x442;&#x43e;&#x432; &#x43d;&#x430; &#x430;&#x43a;&#x442;&#x438;&#x432;&#x43d;&#x43e;&#x441;&#x442;&#x44c;): void" ID="ID_533644800" CREATED="1538811242413" MODIFIED="1538811302775"/>
</node>
</node>
<node TEXT="Tcp_Part" POSITION="left" ID="ID_1544755860" CREATED="1538810061074" MODIFIED="1538810326944">
<edge COLOR="#7c0000"/>
<hook NAME="FirstGroupNode"/>
</node>
</node>
</map>
