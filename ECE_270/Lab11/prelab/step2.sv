module wordcmp (
  input [47:0] guessed, selected,
  output [5:0] in_word, in_place
);
  
  assign in_place = {
    (selected[47:40] == guessed[47:40]),
    (selected[39:32] == guessed[39:32]),
    (selected[31:24] == guessed[31:24]),
    (selected[23:16] == guessed[23:16]),
    (selected[15:8] == guessed[15:8]),
    (selected[7:0] == guessed[7:0])
  };
  
  always_comb 
  begin
    case(guessed[7:0])
      selected[47:40] :  in_word[0] = 1;
      selected[39:32] :  in_word[0] = 1;
      selected[31:24] :  in_word[0] = 1;
      selected[23:16] :  in_word[0] = 1;
      selected[15:8]  :  in_word[0] = 1;
      default         :  in_word[0] = 0;
    endcase
    case(guessed[15:8])
      selected[47:40] :  in_word[1] = 1;
      selected[39:32] :  in_word[1] = 1;
      selected[31:24] :  in_word[1] = 1;
      selected[23:16] :  in_word[1] = 1;
      selected[7:0]   :  in_word[1] = 1;
      default         :  in_word[1] = 0;
    endcase
    case(guessed[23:16])
      selected[47:40] :  in_word[2] = 1;
      selected[39:32] :  in_word[2] = 1;
      selected[31:24] :  in_word[2] = 1;
      selected[15:8]  :  in_word[2] = 1;
      selected[7:0]   :  in_word[2] = 1;
      default         :  in_word[2] = 0;
    endcase
    case(guessed[31:24])
      selected[47:40] :  in_word[3] = 1;
      selected[39:32] :  in_word[3] = 1;
      selected[23:16] :  in_word[3] = 1;
      selected[15:8]  :  in_word[3] = 1;
      selected[7:0]   :  in_word[3] = 1;
      default         :  in_word[3] = 0;
    endcase
    case(guessed[39:32])
      selected[47:40] :  in_word[4] = 1;
      selected[31:24] :  in_word[4] = 1;
      selected[23:16] :  in_word[4] = 1;
      selected[15:8]  :  in_word[4] = 1;
      selected[7:0]   :  in_word[4] = 1;
      default         :  in_word[4] = 0;
    endcase
    case(guessed[47:40])
      selected[39:32] :  in_word[5] = 1;
      selected[31:24] :  in_word[5] = 1;
      selected[23:16] :  in_word[5] = 1;
      selected[15:8]  :  in_word[5] = 1;
      selected[7:0]   :  in_word[5] = 1;
      default         :  in_word[5] = 0;
    endcase
  end
endmodule