vecino_izq([H|[Ht|T]],Vecino_Izq,Vecino_Der):-(H = Vecino_Izq,Ht = Vecino_Der);
 
vecino_izq([Ht|T],Vecino_Izq,Vecino_Der).
 
vecino([H|T],Pista_1,Pista_2):-vecino_izq([H|T],Pista_1,Pista_2);vecino_izq([H|T],Pista_2,Pista_1).
 
casas:- Sol = [ [1,_,_,_,_,hungaro],
        [2,_,_,azul,_,_],
        [3,_,cava,_,_,_],
        [4,_,_,_,_,_],
        [5,_,_,_,_,_] ],
        member( [_,_,_,roja,_,peru] , Sol),
        member( [_,perro,_,_,_,frances] , Sol),
        member( [_,_,_,_,pintor,japones] , Sol),
        member( [_,_,ron,_,_,chino] , Sol),
        member( [1,_,_,_,_,hungaro] , Sol),
        member( [_,_,conac,verde,_,_] , Sol),
        vecino_izq( Sol,[_,_,_,verde,_,_],[_,_,_,blanca,_,_]),
        member( [_,caracoles,_,_,escultor,_] , Sol),
        member( [_,_,_,amarillo,actor,_] , Sol),
        member( [3,_,cava,_,_,_] , Sol),
        vecino( Sol,[_,_,_,_,actor,_],[_,caballo,_,_,_,_]),
        vecino( Sol,[_,_,_,_,_,hungaro],[_,_,_,azul,_,_]),
        member( [_,_,whisky,_,notario,_] , Sol),
        vecino( Sol,[_,_,_,_,medico,_],[_,ardilla,_,_,_,_]),
        write(Sol), nl,!.
