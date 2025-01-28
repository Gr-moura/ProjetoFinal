import { useEffect, useState } from "react";
import "./Board.css";
import { useLocation } from "react-router-dom";
import { BoardCell } from "../../components/BoardCell/BoardCell";
import { WinOverlay } from "../../components/WinOverlay/WinOverlay";

import JogoDaVelhaWasm from "../../../cpp/wasm/JogoDaVelha.wasm?init";
import Ligue4Wasm from "../../../cpp/wasm/Ligue4.wasm?init";
import ReversiWasm from "../../../cpp/wasm/Reversi.wasm?init";


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
    //@ts-ignore
    const {height, widht, gameName, dificulty, playernames}:boardProps = location.state || 0;

    const [playerTurn, setPlayerTurn] = useState(1);
    const [clickedCells, setClickedCells] = useState<number[][]>([]);
    const [reset, setReset] = useState(false);
    const [gameEnded, setGameEnded] = useState<gameEndedType>({
        winnerplayer:"none",
        wintype:"none",
    });

    const abs = (a:number)=>{
        if(a<0) return -a;
        if(a>0) return a;
        return 1;
    }

    //generating a array to register the clicked cells
    const generateClickArray = () => {
        let newArray:number[][] = [];
        for(let x=0; x<widht; x++){
            newArray.push([]);
            for(let y=0; y<height; y++){
                newArray[x].push(0);
            }
        }
        //Reversi has a different starting board
        if(gameName==="Reversi"){
            newArray[3][3] = 1;
            newArray[4][3] = 2;
            newArray[3][4] = 2;
            newArray[4][4] = 1;
        }
        //updating board
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
            // @ts-ignore
            for(let i=0; i<players.length; i++){
                // @ts-ignore
                if(players[i].playerNick===playernick){
                    // @ts-ignore
                    for(let ii=0; ii<players[i].score.length; ii++){
                        // @ts-ignore
                        if(players[i].score[ii].gameName===gameName){
                            if(type=="win"){
                                // @ts-ignore
                                players[i].score[ii].wins = players[i].score[ii].wins+1;
                            }
                            if(type=="tie"){
                                // @ts-ignore
                                players[i].score[ii].ties = players[i].score[ii].ties+1;
                            }
                            if(type=="loss"){
                                // @ts-ignore
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


    const checkForWinJOGODAVELHA = (updatedClickArray:number[][])=>{
        JogoDaVelhaWasm().then((instance)=>{
            for(let coluna=0; coluna<updatedClickArray.length; coluna++){
                for(let linha=0; linha<updatedClickArray[coluna].length; linha++){
                    if(updatedClickArray[coluna][linha]==playerTurn){
                        // @ts-ignore
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

    const updateBoardCellsLIG4 = (updatedClickArray:number[][], position:{x:number, y:number})=>{
        let firstfreeposition = -1;
        for(let i=0; i<updatedClickArray[position.x].length; i++){
            if(updatedClickArray[position.x][i]==0){
                firstfreeposition = i;
            }
        }
        if(firstfreeposition==-1) return false;
        updatedClickArray[position.x][firstfreeposition] = playerTurn;
        setPlayerTurn(playerTurn==1? 2:1);
    }
    const checkForWinLIG4 = (updatedClickArray:number[][])=>{
        Ligue4Wasm().then((instance)=>{
            for(let coluna=0; coluna<updatedClickArray.length; coluna++){
                for(let linha=0; linha<updatedClickArray[coluna].length; linha++){
                    if(updatedClickArray[coluna][linha]==playerTurn){
                        // @ts-ignore
                        if(instance.exports.jogar(linha, coluna, playerTurn)){
                            saveScore(playernames[playerTurn-1], "win");
                            saveScore(playernames[playerTurn-1?0:1], "loss");
                            setGameEnded({winnerplayer:playernames[playerTurn-1], wintype:"win"});
                        };
                    }
                }
            }
        })
    }

    const updateBoardCellsREVERSI = (updatedClickArray:number[][], position:{x:number, y:number})=>{
        //updading wasm instance with past board plays
        const updateREVERSIwasmInstance = (instance:any, updatedClickArray:number[][])=>{
            for(let coluna=0; coluna<updatedClickArray.length; coluna++){
                for(let linha=0; linha<updatedClickArray[coluna].length; linha++){
                    if(updatedClickArray[coluna][linha]==1 || updatedClickArray[coluna][linha]==2){
                        // @ts-ignore
                        instance.exports.colocarNoTabuleiro(linha, coluna, updatedClickArray[coluna][linha]);
                    }
                }
            }
        }
        //checking if a move is valid, playing and fliping pieces
        const validateREVERSIflip = (instance:any, position:{x:number, y:number}, updatedClickArray:number[][]) => {
            // @ts-ignore
            let anchorLine = instance.exports.movimentoValidoY(playerTurn, position.y, position.x);
            // @ts-ignore
            let anchorColumn = instance.exports.movimentoValidoX(playerTurn, position.y, position.x);
            if(anchorLine==-1 || anchorColumn==-1){
                return false;
            }
            // if move is valid, playing it and fliping other pieces
            else{
                updatedClickArray[position.x][position.y] = playerTurn;
                const direction = [
                    (position.x-anchorColumn)/abs(position.x-anchorColumn), 
                    (position.y-anchorLine)/abs(position.y-anchorLine)
                ];
                let i=0;
                while((position.x-direction[0]*i!=anchorColumn)||(position.y-direction[1]*i!=anchorLine)){
                    i++;
                    updatedClickArray[position.x-direction[0]*i][position.y-direction[1]*i] = playerTurn;
                }
            }
            return true;
        }
        //calling a reversi instance
        ReversiWasm().then((instance)=>{
            let changeTurn=false;
            updateREVERSIwasmInstance(instance, updatedClickArray);
            changeTurn = validateREVERSIflip(instance, position, updatedClickArray);
            updateREVERSIwasmInstance(instance, updatedClickArray);
            validateREVERSIflip(instance, position, updatedClickArray);
            updateREVERSIwasmInstance(instance, updatedClickArray);
            validateREVERSIflip(instance, position, updatedClickArray);
            updateREVERSIwasmInstance(instance, updatedClickArray);
            validateREVERSIflip(instance, position, updatedClickArray);
            if(changeTurn) setPlayerTurn(playerTurn==1?2:1);
        })
    }
    const checkForWinREVERSI = (updatedClickArray:number[][])=>{
        ReversiWasm().then((instance)=>{
            for(let coluna=0; coluna<updatedClickArray.length; coluna++){
                for(let linha=0; linha<updatedClickArray[coluna].length; linha++){
                    if(updatedClickArray[coluna][linha]==1 || updatedClickArray[coluna][linha]==2){
                        // @ts-ignore
                        instance.exports.colocarNoTabuleiro(linha, coluna, updatedClickArray[coluna][linha]);
                    }
                }
            }
            // @ts-ignore
            const winner = instance.exports.checarVencedor(playerTurn);
            if(winner!=-1){
                if(winner==0){
                    saveScore(playernames[0], "tie");
                    saveScore(playernames[1], "tie");
                    setGameEnded({winnerplayer:"none", wintype:"tie"});
                }
                else{
                    saveScore(playernames[winner-1], "win");
                    saveScore(playernames[winner-1?0:1], "loss");
                    setGameEnded({winnerplayer:playernames[winner-1], wintype:"win"});
                }
            }
        })
    }


    const handleClickedCell = (position:{x:number, y:number}) => {
        let updatedClickArray:number[][] = [...clickedCells];
        //updating board cells
        if(gameName==="Ligue Quatro"){
            updateBoardCellsLIG4(updatedClickArray, position);
            checkForWinLIG4(updatedClickArray);
        }
        else if(gameName==="Reversi"){
            updateBoardCellsREVERSI(updatedClickArray, position);
            checkForWinREVERSI(updatedClickArray);
        }
        else{
            updatedClickArray[position.x][position.y] = playerTurn;
            checkForWinJOGODAVELHA(updatedClickArray);
            setPlayerTurn(playerTurn==1? 2:1);
        }
        setClickedCells(updatedClickArray);
        //checking if the game ended in tie (due to board filling up)
        checkForTie();
    }

    useEffect(()=>{
        setReset(false);
        setPlayerTurn(1);
        setGameEnded({winnerplayer:"none",wintype:"none"});
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
                    <ul key={index1.toString()}>
                        {/*@ts-ignore*/}
                        {item.map((item, index2)=>(
                            <li key={index1.toString()+index2.toString()}>    
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