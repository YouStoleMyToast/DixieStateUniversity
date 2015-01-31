" Zombie apocalypse simulator "

Object subclass: Zombie [
    | board size |
    setup: s [
        size := s.
        board := Array new: size.
        1 to: size do: [ :x |
            board at: x put: (Array new: size).
            1 to: size do: [ :i |
                 (board at: x) at: i put: '-'
            ]
        ]
    ]

    print [
        1 to: size do: [ :y |
            | row |
            row := board at: y.
            1 to: size do: [ :x |
                Transcript show: (row at: x)
            ].
            Transcript cr
        ].
        Transcript cr
    ]

    get: x by: y [
        ^(board at: y) at: x
    ]

    set: x by: y to: v [
        (board at: y) at: x put: v
    ]

    cat: x by: y [
        self set: x by: y to: '!'
    ]

    zombie: x by: y [
        (((x between: 1 and: size) and: [y between: 1 and: size]) and: [(self get: x by: y) = '-']) ifTrue: [
            self set: x by: y to: '@'.
            self print.
            self zombie: (x-1) by: y.
            self zombie: (x+1) by: y.
            self zombie: x by: (y-1).
            self zombie: x by: (y+1)
        ]
    ]
]

" --!!--- "
" -!--!-- "
" -!--!-- "
" --!!--- "
" ---@--- "
" ------- "
" ------- "

z := Zombie new.
z setup: 7.
z cat: 3 by: 1.
z cat: 4 by: 1.
z cat: 2 by: 2.
z cat: 2 by: 3.
z cat: 3 by: 4.
z cat: 4 by: 4.
z cat: 5 by: 2.
z cat: 5 by: 3.
z print.

z zombie: 1 by: 1.
