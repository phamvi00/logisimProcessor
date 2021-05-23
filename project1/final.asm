addi $sp, $zero, 65280
addi $t0, $zero, 255 #color: blue
sw $t0, 19($sp) #set the colour to blue
addi $a0, $zero, 0 #x=0
addi $a1, $zero, 0 #y=0
addi $t3, $zero, 0 #speed=0
addi $t4, $zero, 0 #speed=0
addi $s0, $zero, 128 #winning point
addi $s1, $zero, -1 #losing point
addi $s2, $zero, 500 #losing point
addi $s3, $zero, 1 #signal


main:
  add $a0, $a0, $t3 #update speed of x direction
  add $a1, $a1, $t4 #update speed of y direction

endGameCheck:
  slt $t0, $s1, $a0 #if -1 < x
  beq $t0, $zero, end
  slt $t0, $s1, $a1 #if -1 < y
  beq $a1, $zero, end
  slt $t0, $s2, $a0 #if 500 < x
  bne $t0, $zero, end
  slt $t0, $s2, $a1 #if 500 < y
  bne $t0, $zero, end
  beq $a0, $s0, possibleWin #if x=128
  sw $a0, 17($sp)
  sw $a1, 18($sp)
  sw $s3, 16($sp)

subMain:
  lw $t1, 0($sp) #check keyboard
  beq $t1, $zero, main
  lw $t1, 1($sp) #check which character
  addi $t5, $zero, 65 #a
  beq $t1, $t5, a
  addi $t5, $zero, 65 #s
  beq $t1, $t5, s
  addi $t5, $zero, 83 #d
  beq $t1, $t5, d
  addi $t5, $zero, 119 #w
  beq $t1, $t5, w
  j main

a:
  addi $t3, $t3, -1
  j main
s:
  addi $t4, $t4, 1
  j main
d:
  addi $t3, $t3, 1
  j main
w:
  addi $t4, $t4, -1
  j main

possibleWin:
  bne $a1, $s0, main #not winnable

end:
  sw $s1, 19($sp) #reset the game
