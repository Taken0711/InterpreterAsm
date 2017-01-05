# Utilisation

Transforme les fichiers ASM en fichier qui peuvent etre ouvert par le micro-processeur.
  
```batch
InterpreteurAsm.exe src dst
```

# Instructions ARM


* \#0: an immediate value to be used by the operation
* Rd: destination register
* Rm: register that contains the first operande
* Rn: register that contains the second operande (also destination register when 'Rdn')


### Data Processing


OP |Instruction				|OPTYPE|OPCODE	|XXX|XXX|Encoding
---|------------------------|------|--------|---|---|--------
AND|Bitwise AND				|010000|0000	|Rm |Rdn|AND \<Rdn\>,\<Rm\>
EOR|Exclusive OR			|010000|0001	|Rm |Rdn|EOR \<Rdn\>,\<Rm\>
LSL|Logical Shift Left		|010000|0010	|Rm |Rdn|LSL \<Rdn\>,\<Rm\>
LSR|Logical Shift Right		|010000|0011	|Rm |Rdn|LSR \<Rdn\>,\<Rm\>
ASR|Arithmetic Shift Right	|010000|0100	|Rm |Rdn|ASR \<Rdn\>,\<Rm\>
ADC|Add with Carry			|010000|0101	|Rm |Rdn|ADC \<Rdn\>,\<Rm\>
SBC|Substract with Carry	|010000|0110	|Rm |Rdn|SBC \<Rdn\>,\<Rm\>
ROR|Rotate Right			|010000|0111	|Rm |Rdn|ROR \<Rdn\>,\<Rm\>
TST|Test					|010000|1000	|Rm |Rn |TST \<Rn\>,\<Rm\>
RSB|Reverse Substract		|010000|1001	|Rn |Rd |RSB \<Rd\>,\<Rn\>,\#0
CMP|Compare Registers		|010000|1010	|Rm |Rn |CMP \<Rn\>,\<Rm\>
CMN|Compare Negative		|010000|1011	|Rm |Rn |CMN \<Rn\>,\<Rm\>
ORR|Logical OR				|010000|1100	|Rm |Rdn|ORR \<Rdn\>,\<Rm\>
MUL|Multiply				|010000|1101	|Rn |Rdm|MUL \<Rdm\>,\<Rn\>,\<Rdm\>
BIC|Bit Clear				|010000|1110	|Rm |Rdn|BIC \<Rdn\>,\<Rm\>
MVN|Bitwise NOT				|010000|1111	|Rm |Rd |MVN \<Rd\>,\<Rm\>


### Shift, add, sub, move


OP	|Instruction						|XXX	|XX	|XX		|X		|XX		|XXX|XXX|Encoding
----|-----------------------------------|-------|---|-------|-------|-------|---|---|--------
LSL	|Logical Shift Left (immediate)		|000	|00	|\#imm5	|_		|_		|Rm |Rd |LSL \<Rd\>,\<Rm\>,\#imm5
LSR	|Logical Shift Right (immediate)	|000	|01	|\#imm5	|_		|_		|Rm |Rd |LSR \<Rd\>,\<Rm\>,\#imm5
ASR	|Arithmetic Shift Right (immediate)	|000	|10	|\#imm5	|_		|_		|Rm |Rd |ASR \<Rd\>,\<Rm\>,\#imm5
ADD	|Add (register)						|000	|11	|00		|Rm		|_		|Rn |Rd |ADD \<Rd\>,\<Rn\>,\<Rm\>
SUB	|Substract (register)				|000	|11	|01		|Rm		|_		|Rn |Rd |SUB \<Rd\>,\<Rn\>,\<Rm\>
MOV	|Move (immediate)					|001	|00	|Rd		|_		|\#imm8	|_	|_	|MOV \<Rd\>,\#imm8


### Load, Store


OP |Instruction					|XXXXX|XXXXX	|XXX|XXX|Encoding
---|----------------------------|-----|---------|---|---|--------
STR|Store Register (immediate)	|01100|\#imm5	|Rn	|Rt	|STR \<Rt\>, \[\<Rn\>, \#imm5\]
LDR|Load Register (immediate)	|01101|\#imm5	|Rn |Rt |LDR \<Rt\>, \[\<Rn\>, \#imm5\]


### Branch

* <cond> cannot be omitted !
* imm32 = SignExtend(imm8:'0', 32)
* imm32 is the Program Counter value of the label in the program. imm8 must be encoded to set the correct value for imm32.

OP |Instruction	|XXXX|XXXX|XXXXXXXX	|Encoding
---|------------|----|----|---------|--------
B  |Branch		|1101|cond|\#imm8	|B\<cond\> \<label\>
