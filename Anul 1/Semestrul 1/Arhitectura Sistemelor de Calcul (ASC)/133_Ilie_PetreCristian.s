    .data
        m: .space 1600
        v: .space 80
        q: .space 1600
        n: .space 4
        sp: .asciiz " "
        br: .asciiz "\n"
        vrol: .space 80
        mal: .asciiz "switch malitios index "
        swi: .asciiz "switch index "
        dp: .asciiz ": "
        host: .asciiz "host index "
        pv: .asciiz "; "
        controller: .asciiz "controller index "
        yes: .asciiz "Yes"
        no: .asciiz "No"
        sir: .space 1600


    .text

    main:
        li $v0,5
        syscall
        move $t0,$v0
        sw $t0,n
        j init_mat

    init_mat:
        li $t1,0
        j init_linie

    init_linie:
        bge $t1,$t0,leg
        li $t2,0
        j init_coloana

    init_coloana:
        bge $t2,$t0,exit_col
        mul $t3,$t1,$t0
        add $t3,$t3,$t2
        li $t4,4
        mul $t3,$t3,$t4
        li $t4,0
        sw $t4,m($t3)
        addi $t2,$t2,1
        j init_coloana

    exit_col:
        addi $t1,$t1,1
        j init_linie

    leg:
        li $v0,5
        syscall
        move $t1,$v0
        li $t2,0
        sw $t0,n
        j loopleg

    loopleg:
        bge $t2,$t1,cont     
        li $v0,5
        syscall
        move $t3,$v0
        li $v0,5
        syscall
        move $t4,$v0
        mul $t5,$t3,$t0
        add $t5,$t5,$t4
        li $t7,4
        mul $t5,$t5,$t7
        li $t6,1
        sw $t6,m($t5)
        mul $t5,$t4,$t0
        add $t5,$t5,$t3
        mul $t5,$t5,$t7
        sw $t6,m($t5)
        addi $t2,$t2,1
        j loopleg

    afis:
        li $t2,0
        li $t3,0
        mul $t4,$t0,$t0
        j loopafis

    loopafis:
        bge $t2,$t4,exit
        lw $t5,m($t3)
        move $a0,$t5
        li $v0,1
        syscall
        addi $t2,$t2,1
        addi $t3,$t3,4
        j loopafis

    cont:
        li $t1,0
        lw $t2,n
        li $t3,0
        j looprol

    looprol:
        bge $t1,$t2,cerinta
        li $v0,5
        syscall
        sw $v0,vrol($t3)
        addi $t1,$t1,1
        addi $t3,$t3,4
        j looprol

    afisvec:
        li $t1,0
        lw $t2,n
        li $t3,0
        j vec

    vec:
        bge $t1,$t2,exit
        lw $t4,vrol($t3)
        move $a0,$t4
        li $v0,1
        syscall
        addi $t1,$t1,1
        addi $t3,$t3,4    
        j vec

    cerinta:
        li $v0,5
        syscall
        move $t3,$v0
        li $t4,1
        beq $t3,$t4,cerinta1
        addi $t4,$t4,1
        beq $t3,$t4,cerinta2
        addi $t4,$t4,1
        beq $t3,$t4,cerinta3

    cerinta1:
        li $t1,0
        li $t2,0
        li $t4,3
        j loopvec

    loopvec:
        bge $t1,$t0,exit
        lw $t3,vrol($t2)
        beq $t3,$t4,malitios
        contloop:
            addi $t1,$t1,1
            addi $t2,$t2,4
            j loopvec

    malitios:
        la $a0,mal
        li $v0,4
        syscall
        move $a0,$t1
        li $v0,1
        syscall
        la $a0,dp
        li $v0,4
        syscall
        j afisarevec
        revenire:
            la $a0,br
            li $v0,4
            syscall
            j contloop

    afisarevec:
        li $t8,0
        mul $t6,$t2,$t0
        j loopafisarevec

    loopafisarevec:
        beq $t8,$t0,revenire
        lw $t7,m($t6)
        li $t9,1
        beq $t7,$t9,afisareind
        contloopafisarevec:
            addi $t8,$t8,1
            addi $t6,$t6,4
            j loopafisarevec

    afisareind:
        mul $t7,$t8,4
        lw $t9,vrol($t7)
        li $t5,1
        beq $t9,$t5,afisarehost
        addi $t5,$t5,1
        beq $t9,$t5,afisareswitch
        addi $t5,$t5,1
        beq $t9,$t5,afisareswitchmalitios
        addi $t5 $t5,1
        beq $t9,$t5,afisarecontroller
        j contloopafisarevec

    afisarehost:
        la $a0,host
        li $v0,4
        syscall
        move $a0,$t8
        li $v0,1
        syscall
        la $a0,pv
        li $v0,4
        syscall
        j contloopafisarevec

    afisareswitch:
        la $a0,swi
        li $v0,4
        syscall
        move $a0,$t8
        li $v0,1
        syscall
        la $a0,pv
        li $v0,4
        syscall
        j contloopafisarevec

    afisareswitchmalitios:
        la $a0,mal
        li $v0,4
        syscall
        move $a0,$t8
        li $v0,1
        syscall
        la $a0,pv
        li $v0,4
        syscall
        j contloopafisarevec

    afisarecontroller:
        la $a0,controller
        li $v0,4
        syscall
        move $a0,$t8
        li $v0,1
        syscall
        la $a0,pv
        li $v0,4
        syscall
        j contloopafisarevec

    cerinta2:
        lw $t0,n
        li $t1,0
        li $t2,0
        j initializare_visited

    initializare_visited:
        bge $t1,$t0,cont_cerinta2
        li $t3,0
        sw $t3,v($t2)
        addi $t1,$t1,1
        addi $t2,$t2,4
        j initializare_visited

    cont_cerinta2:
        li $t1,0
        li $t2,0
        li $t3,0
        li $t4,0
        j queue

    queue:
        li $t8,0
        sw $t8,q($t1)
        addi $t1,$t1,1
        li $t8,1
        sw $t8,v($t2)
        j while1

    while1:
        beq $t2,$t1,brvisit
        mul $t5,$t2,4
        lw $t3,q($t5)
        addi $t2,$t2,1
        li $t9,1
        mul $t5,$t3,4
        lw $t8,vrol($t5)
        beq $t8,$t9,printare
        contprintare:
            li $t4,0
            j while2

    printare:
        la $a0,host
        li $v0,4
        syscall
        move $a0,$t3
        li $v0,1
        syscall
        la $a0,pv
        li $v0,4
        syscall
        j contprintare

    while2:
        bge $t4,$t0,while1
        li $t9,1
        mul $t8,$t0,$t3
        add $t8,$t8,$t4
        mul $t8,$t8,4
        lw $t7,m($t8)
        beq $t9,$t7,ifgraph
        contifgraph:
            addi $t4,$t4,1
            j while2

    ifgraph:
        mul $t7,$t4,4
        lw $t8,v($t7)
        li $t9,1
        bne $t8,$t9,ifvisit
        j contifgraph

    ifvisit:
        mul $t7,$t1,4
        sw $t4,q($t7)
        addi $t1,$t1,1
        li $t7,1
        mul $t8,$t4,4
        sw $t7,v($t8)
        j contifgraph

    brvisit:
        la $a0,br
        li $v0,4
        syscall
        li $t1,0
        li $t2,0
        j verificvisit

    verificvisit:
        bge $t1,$t0,succes
        lw $t3,v($t2)
        li $t4,1
        bne $t3,$t4,esec
        addi $t1,$t1,1
        addi $t2,$t2,4
        j verificvisit

    esec:
        la $a0,no
        li $v0,4
        syscall
        j exit

    succes:
        la $a0,yes
        li $v0,4
        syscall
        j exit

    cerinta3:
        li $v0,5
        syscall
        move $t0,$v0
        li $v0,5
        syscall
        move $t0,$v0
        la $a0,sir
        li $a1,1000
        li $v0,8
        syscall
        li $t0,0
        lb $t2,br
        j cerinta3loop

    cerinta3loop:
        lb $t1,sir($t0)
        beq $t1,$t2,exit
        lb $a0,sir($t0)
        li $v0,11
        syscall
        addi $t0,$t0,1
        j cerinta3loop

    exit:
        li $v0,10
        syscall















