// Microsemi Corporation Proprietary and Confidential
// Copyright 2011 Microsemi Corporation.  All rights reserved.
// ANY USE OR REDISTRIBUTION IN PART OR IN WHOLE MUST BE HANDLED IN
// ACCORDANCE WITH THE ACTEL LICENSE AGREEMENT AND MUST BE APPROVED
// IN ADVANCE IN WRITING.
// SVN Revision Information:
// SVN $Revision: 24054 $
// SVN $Date: 2014-12-08 10:43:40 +0000 (Mon, 08 Dec 2014) $
module
CAPB3O
(
PCLK
,
PRESETN
,
PENABLE
,
PSEL
,
PADDR
,
PWRITE
,
PWDATA
,
PRDATA
,
CAPB3I
)
;
parameter
SYNC_RESET
=
0
;
parameter
[
5
:
0
]
APB_DWIDTH
=
32
;
parameter
[
5
:
0
]
MADDR_BITS
=
32
;
input
PCLK
;
input
PRESETN
;
input
PENABLE
;
input
PSEL
;
input
[
31
:
0
]
PADDR
;
input
PWRITE
;
input
[
31
:
0
]
PWDATA
;
output
[
31
:
0
]
PRDATA
;
output
[
31
:
0
]
CAPB3I
;
reg
[
31
:
0
]
PRDATA
;
reg
[
31
:
0
]
CAPB3I
;
wire
CAPB3l
;
wire
CAPB3OI
;
assign
CAPB3l
=
(
SYNC_RESET
==
1
)
?
1
'b
1
:
PRESETN
;
assign
CAPB3OI
=
(
SYNC_RESET
==
1
)
?
PRESETN
:
1
'b
1
;
always
@
(
posedge
PCLK
or
negedge
CAPB3l
)
begin
if
(
(
!
CAPB3l
)
||
(
!
CAPB3OI
)
)
begin
CAPB3I
<=
32
'b
0
;
end
else
begin
if
(
PSEL
&&
PENABLE
&&
PWRITE
)
begin
if
(
APB_DWIDTH
==
32
)
begin
if
(
PADDR
[
MADDR_BITS
-
4
-
1
:
0
]
==
{
MADDR_BITS
-
4
{
1
'b
0
}
}
)
begin
CAPB3I
<=
PWDATA
;
end
end
if
(
APB_DWIDTH
==
16
)
begin
if
(
PADDR
[
MADDR_BITS
-
4
-
1
:
4
]
==
{
MADDR_BITS
-
4
-
4
{
1
'b
0
}
}
)
begin
case
(
PADDR
[
3
:
0
]
)
4
'b
0000
:
CAPB3I
[
15
:
0
]
<=
PWDATA
[
15
:
0
]
;
4
'b
0100
:
CAPB3I
[
31
:
16
]
<=
PWDATA
[
15
:
0
]
;
4
'b
1000
:
CAPB3I
<=
CAPB3I
;
4
'b
1100
:
CAPB3I
<=
CAPB3I
;
endcase
end
end
if
(
APB_DWIDTH
==
8
)
begin
if
(
PADDR
[
MADDR_BITS
-
4
-
1
:
4
]
==
{
MADDR_BITS
-
4
-
4
{
1
'b
0
}
}
)
begin
case
(
PADDR
[
3
:
0
]
)
4
'b
0000
:
CAPB3I
[
7
:
0
]
<=
PWDATA
[
7
:
0
]
;
4
'b
0100
:
CAPB3I
[
15
:
8
]
<=
PWDATA
[
7
:
0
]
;
4
'b
1000
:
CAPB3I
[
23
:
16
]
<=
PWDATA
[
7
:
0
]
;
4
'b
1100
:
CAPB3I
[
31
:
24
]
<=
PWDATA
[
7
:
0
]
;
endcase
end
end
end
end
end
always
@
(
*
)
begin
PRDATA
=
32
'b
0
;
if
(
APB_DWIDTH
==
32
)
begin
if
(
PADDR
[
MADDR_BITS
-
4
-
1
:
0
]
==
{
MADDR_BITS
-
4
{
1
'b
0
}
}
)
begin
PRDATA
=
CAPB3I
;
end
end
if
(
APB_DWIDTH
==
16
)
begin
if
(
PADDR
[
MADDR_BITS
-
4
-
1
:
4
]
==
{
MADDR_BITS
-
4
-
4
{
1
'b
0
}
}
)
begin
case
(
PADDR
[
3
:
0
]
)
4
'b
0000
:
PRDATA
[
15
:
0
]
=
CAPB3I
[
15
:
0
]
;
4
'b
0100
:
PRDATA
[
15
:
0
]
=
CAPB3I
[
31
:
16
]
;
4
'b
1000
:
PRDATA
=
32
'b
0
;
4
'b
1100
:
PRDATA
=
32
'b
0
;
endcase
end
end
if
(
APB_DWIDTH
==
8
)
begin
if
(
PADDR
[
MADDR_BITS
-
4
-
1
:
4
]
==
{
MADDR_BITS
-
4
-
4
{
1
'b
0
}
}
)
begin
case
(
PADDR
[
3
:
0
]
)
4
'b
0000
:
PRDATA
[
7
:
0
]
=
CAPB3I
[
7
:
0
]
;
4
'b
0100
:
PRDATA
[
7
:
0
]
=
CAPB3I
[
15
:
8
]
;
4
'b
1000
:
PRDATA
[
7
:
0
]
=
CAPB3I
[
23
:
16
]
;
4
'b
1100
:
PRDATA
[
7
:
0
]
=
CAPB3I
[
31
:
24
]
;
endcase
end
end
end
endmodule