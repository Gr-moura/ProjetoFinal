import { useEffect, useState } from "react";
import "./Board.css";
import { useLocation } from "react-router-dom";
import { BoardCell } from "../../components/BoardCell/BoardCell";
import { WinOverlay } from "../../components/WinOverlay/WinOverlay";

import JogoDaVelhaWasm from "../../../cpp/wasm/JogoDaVelha.wasm?init";


interface boardProps{
    height:number,
    widht:number,
    gameName:string
    dificulty:number
    playernames:string[];
}
interface gameEndedType{
        wintype:string;
        winnerplayer:string;
}


export const Board = ()=>{
    const location = useLocation();
    const {height, widht, gameName, dificulty, playernames}:boardProps = location.state || 0;

    const [playerTurn, setPlayerTurn] = useState(1);
    const [clickedCells, setClickedCells] = useState<number[][]>([]);
    const [reset, setReset] = useState(false);
    const [gameEnded, setGameEnded] = useState<gameEndedType>({
        winnerplayer:"none",
        wintype:"none",
    });

    //generating a array to register the clicked cells
    const generateClickArray = () => {
        let newArray:number[][] = [];
        for(let x=0; x<widht; x++){
            newArray.push([]);
            for(let y=0; y<height; y++){
                newArray[x].push(0);
            }
        }
        setClickedCells(newArray);
    }

    //chekcing to see if there was a tie because the bord is filled
    const checkForTie = () => {
        let boardfilled = true;
        clickedCells.forEach(column => {
            column.forEach(cellclicked => {
                if(cellclicked==0){
                    boardfilled = false;
                }
            })
        });
        if(boardfilled){
            saveScore(playernames[playerTurn-1], "tie");
            saveScore(playernames[playerTurn-1?0:1], "tie");
            setGameEnded({wintype:"tie", winnerplayer:"none"});
            return;
        } 
    }
    const saveScore = (playernick:string, type:string)=>{
        let players = localStorage.getItem("players");
        if(players){
            players = JSON.parse(players);
            for(let i=0; i<players.length; i++){
                if(players[i].playerNick===playernick){
                    for(let ii=0; ii<players[i].score.length; ii++){
                        if(players[i].score[ii].gameName===gameName){
                            if(type=="win"){
                                players[i].score[ii].wins = players[i].score[ii].wins+1;
                            }
                            if(type=="tie"){
                                players[i].score[ii].ties = players[i].score[ii].ties+1;
                            }
                            if(type=="loss"){
                                players[i].score[ii].losses = players[i].score[ii].losses+1;
                            }
                        }
                    }
                }
            }
            localStorage.setItem("players", JSON.stringify(players));
            return true;
        }
        return false;
    }

    const handleClickedCell = (position:{x:number, y:number}) => {
        //updating board cells
        let updatedClickArray:number[][] = [...clickedCells];
        updatedClickArray[position.x][position.y] = playerTurn;
        setClickedCells(updatedClickArray);
        //checking if the game was won
        if(gameName==="Jogo da Velha"){
            JogoDaVelhaWasm().then((instance)=>{
                for(let coluna=0; coluna<updatedClickArray.length; coluna++){
                    for(let linha=0; linha<updatedClickArray[coluna].length; linha++){
                        if(updatedClickArray[coluna][linha]==playerTurn){
                            if(instance.exports.jogar(linha, coluna, playerTurn)){
                                saveScore(playernames[playerTurn-1], "win");
                                saveScore(playernames[playerTurn-1?0:1], "loss");
                                setGameEnded({winnerplayer:playernames[playerTurn-1], wintype:"win"});
                            };
                        }
                    }
                }
            });
        }
        //checking if the game ended in tie
        checkForTie();
        //changing player turn
        setPlayerTurn(playerTurn==1? 2:1);
    }

    useEffect(()=>{
        setReset(false);
        setPlayerTurn(1);
        setGameEnded({
            winnerplayer:"none",
            wintype:"none"
        })
        generateClickArray();
    }, [reset, widht, length])

    return(
        <div className="boardbody">
            <h1 className="gametitle">{gameName}</h1>
            <div style={{display:"flex"}}>
                <h3 style={{marginRight:"10px"}}>turno de </h3>
                <h3 style={playerTurn==1?{color:"#8ceeb3"}:{color:"#ef6f5b"}}>{playernames[playerTurn-1]}</h3>
            </div>
            <ul className="board"> 
                {clickedCells.map((item, index1) => (
                    <ul>
                        {item.map((item, index2)=>(
                            <li>    
                                <BoardCell 
                                    position={{x:index1, y:index2}} 
                                    clickedBy={clickedCells[index1][index2]!=0?"player"+clickedCells[index1][index2].toString():""} 
                                    handleClickedCell={handleClickedCell}
                                />
                            </li>
                        ))}
                    </ul>
                ))}
            </ul>
            <WinOverlay 
                winnerplayer={gameEnded.winnerplayer} 
                wintype={gameEnded.wintype} 
                reset={setReset}
                className={gameEnded.wintype==="none"?"hidden":"show"}
            />
        </div>
    )
}