/**
 * "How to Write a Spelling Corrector" in Go
 * 
 * See original at http://norvig.com/spell-correct.html
 *
 * To compile, link, and run do:
 *   6g spell.go && 6l spell.6 && time ./6.out spellin < big.txt   
 */

package main

import (
    "os"
    "fmt"
    "bufio"
    "unicode"
)

func train() map[string] int {
    var word[1024] byte
    i := 0
    words := map[string] int {}
    reader := bufio.NewReader(os.Stdin)
    for {
       c,_ := reader.ReadByte() 
       c = byte(unicode.ToLower(int(c)))
       if c == 0 { break }
       if c  < 'a' || c > 'z' {
            words[string(word[0:i])]++
            i=0
        } else {
            word[i] = c
            i++
        }
    }
    return words
}

func calc_edits1(word string) []string {
    splits := [][]string{}
    for i := 0; i <= len(word); i++ {
        split := []string{word[0:i],word[i:]}
        splits = append(splits, split)
    }
   
    deletes := []string{} 
    for _,s := range splits {
        if len(s[1]) > 0 {
            deletes = append(deletes, s[0] + s[1][1:])
        }
    }

    replaces := []string{} 
    for _,s := range splits {
        if len(s[1]) > 0 {
            for _,c := range "abcdefghjkilmnopqrstuvwxyz" {
                replaces = append(replaces, s[0] + string(c) + s[1][1:])
            }
        }
    }

    transposes := []string{}
    for _,s := range splits {
        if len(s[1]) > 1 {
            transpose := s[0] + s[1][1:2] + s[1][0:1] + s[1][2:]
            transposes = append(transposes, transpose)
        }
    }

    inserts := []string{}
    for _,s := range splits {
        for _,c := range "abcdefghjkilmnopqrstuvwxyz" {
            insert := s[0] + string(c) + s[1]
            inserts = append(inserts, insert)
        }
    }

    all := []string{}
    all = append(all, deletes...)
    all = append(all, replaces...)
    all = append(all, transposes...)
    all = append(all, inserts...)
 
    return all
}

func known_words(nwords map[string] int, words []string) []string {
    known_words := []string{}
    for _,word := range words {
        if nwords[word] != 0 {
            known_words = append(known_words, word)
        } 
    }
    return known_words
}

func findmax(nwords map[string] int, kwords []string) string {
    max := 0
    max_word := ""
    for _,kword := range kwords {
        if (nwords[kword] > max) {
            max = nwords[kword]
            max_word = kword
        }
    }
    return max_word
}

func correct(nwords map[string] int, word string) string {
    kwords := known_words(nwords, []string {word})
    var edits1 []string
    if len(kwords) == 0 {
        edits1 = calc_edits1(word)
        kwords = known_words(nwords, edits1)
    }
    if len(kwords) == 0 {
        for _,edit1 := range edits1 {
            edits2 := calc_edits1(edit1)
            kwords = append(kwords, known_words(nwords, edits2)...)
        }
    }
    return findmax(nwords, kwords)
}

func usage() {
    fmt.Println("Usage: " + os.Args[0] + " word < big.txt")
}

func main() {
    if len(os.Args) < 2 { 
        usage()
        return;
    }
    nwords := train()
    correction := correct(nwords, os.Args[1])
    fmt.Println(correction)
}
