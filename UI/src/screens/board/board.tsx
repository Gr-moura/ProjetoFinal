import { useEffect, useState } from "react";
import "./Board.css";
import { useLocation } from "react-router-dom";
import { BoardCell } from "../../components/BoardCell/BoardCell";
import { WinOverlay } from "../../components/WinOverlay/WinOverlay";

import JogoDaVelhaWasm from "../../../cpp/wasm/JogoDaVelha.wasm?init";
import JogoDaVelhaAIWasm from "../../../cpp/wasm/JogoDaVelhaAi.wasm?init";

import Ligue4Wasm from "../../../cpp/wasm/Ligue4.wasm?init";
import ReversiWasm from "../../../cpp/wasm/Reversi.wasm?init";


/**
 * @interface boardProps
 * @brief Propriedades do tabuleiro do jogo.
 * @property {number} height Altura do tabuleiro.
 * @property {number} widht Largura do tabuleiro.
 * @property {string} gameName Nome do jogo.
 * @property {number} dificulty Dificuldade do jogo.
 * @property {string[]} playernames Nomes dos jogadores.
 */
interface boardProps{
    height:number,
    widht:number,
    gameName:string
    dificulty:number
    playernames:string[];
}

/**
 * @interface gameEndedType
 * @brief Tipo que define o estado do jogo ao terminar.
 * @property {string} wintype Tipo de vitória (ex: "win", "tie").
 * @property {string} winnerplayer Nome do jogador vencedor.
 */
interface gameEndedType{
        wintype:string;
        winnerplayer:string;
}


/**
 * @brief Componente principal do tabuleiro do jogo.
 * @return {JSX.Element} Retorna o componente do tabuleiro.
 */
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

    /**
     * @brief Função para calcular o valor absoluto de um número.
     * @param {number} a Número de entrada.
     * @return {number} Valor absoluto de `a`.
     */
    const abs = (a:number)=>{
        if(a<0) return -a;
        if(a>0) return a;
        return 1;
    }

    /**
     * @brief Gera um array para registrar as células clicadas.
     * @details Inicializa o tabuleiro com zeros e configura o estado inicial do Reversi, se necessário.
     */
    const generateClickArray = () => {
        let newArray:number[][] = [];
        for(let x=0; x<widht; x++){
            newArray.push([]);
            for(let y=0; y<height; y++){
                newArray[x].push(0);
            }
        }
        // Reversi tem um tabuleiro inicial diferente
        if(gameName==="Reversi"){
            newArray[3][3] = 1;
            newArray[4][3] = 2;
            newArray[3][4] = 2;
            newArray[4][4] = 1;
        }
        // Atualiza o estado do tabuleiro
        setClickedCells(newArray);
    }

    /**
     * @brief Verifica se houve um empate devido ao tabuleiro estar completamente preenchido.
     */
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

    /**
     * @brief Salva a pontuação do jogador no localStorage.
     * @param {string} playernick Nome do jogador.
     * @param {string} type Tipo de pontuação (ex: "win", "tie", "loss").
     * @return {boolean} Retorna `true` se a pontuação foi salva com sucesso, caso contrário `false`.
     */
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

    /**
     * @brief Verifica se houve uma vitória no Jogo da Velha.
     * @param {number[][]} updatedClickArray Matriz atualizada das células clicadas.
     */
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

    /**
     * @brief Atualiza as células do tabuleiro no Ligue 4.
     * @param {number[][]} updatedClickArray Matriz atualizada das células clicadas.
     * @param {{x: number, y: number}} position Posição da célula clicada.
     * @return {boolean} Retorna `false` se a coluna estiver cheia, caso contrário `true`.
     */
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
    /**
     * @brief Verifica se houve uma vitória no Ligue 4.
     * @param {number[][]} updatedClickArray Matriz atualizada das células clicadas.
     */
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

    /**
     * @brief Atualiza as células do tabuleiro no Reversi.
     * @param {number[][]} updatedClickArray Matriz atualizada das células clicadas.
     * @param {{x: number, y: number}} position Posição da célula clicada.
     */
    const updateBoardCellsREVERSI = (updatedClickArray:number[][], position:{x:number, y:number})=>{
        // Atualiza a instância WASM com as jogadas anteriores
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
        // Verifica se um movimento é válido, joga e vira as peças
        const validateREVERSIflip = (instance:any, position:{x:number, y:number}, updatedClickArray:number[][]) => {
            // @ts-ignore
            let anchorLine = instance.exports.movimentoValidoY(playerTurn, position.y, position.x);
            // @ts-ignore
            let anchorColumn = instance.exports.movimentoValidoX(playerTurn, position.y, position.x);
            if(anchorLine==-1 || anchorColumn==-1){
                return false;
            }
            // Se o movimento for válido, joga e vira as peças
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
        // Chama uma instância do Reversi
        ReversiWasm().then((instance)=>{
            let changeTurn=false;
            updateREVERSIwasmInstance(instance, updatedClickArray);
            while(validateREVERSIflip(instance, position,updatedClickArray)){
                changeTurn=true;
                updateREVERSIwasmInstance(instance, updatedClickArray);
            }
            if(changeTurn) setPlayerTurn(playerTurn==1?2:1);
        })
    }
    /**
     * @brief Verifica se houve uma vitória no Reversi.
     * @param {number[][]} updatedClickArray Matriz atualizada das células clicadas.
     */
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
            // @ts-ignore
            const winner2 = instance.exports.checarVencedor(playerTurn==1?2:1);
            if(winner!=-1 && winner2!=-1){
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
            if(winner!=-1 && winner2==-1){
                setPlayerTurn(playerTurn==1?2:1);
            }
        })
    }

    /**
     * @brief Manipula o clique em uma célula do tabuleiro.
     * @param {{x: number, y: number}} position Posição da célula clicada.
     */
    const handleClickedCell = (position:{x:number, y:number}) => {
        let updatedClickArray:number[][] = [...clickedCells];
        // Atualizando o estado do tabuleiro para cada jogo
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
        checkForTie();
    }

    /**
     * @brief Efeito executado toda vez que um jogo é iniciado.
     */
    useEffect(()=>{
        setReset(false);
        if(!reset){
            const turn_choice = Math.random()<0.5?1:2;
            console.log("escolha do turno", turn_choice);
            setPlayerTurn(turn_choice);
            setGameEnded({winnerplayer:"none",wintype:"none"});
            generateClickArray();
        }
    }, [reset, widht, length]);
    
    /**
     * @brief Realiza a jogada da IA.
     */
    const makeAImove = () => {
        setTimeout(()=>{
            JogoDaVelhaAIWasm().then((instance)=>{
                // Atualizando o tabuleiro da instância da IA
                for(let column=0; column<clickedCells.length; column++){
                    for(let line=0; line<clickedCells[column].length; line++){
                        // A IA usa um sistema de tabuleiro numerado (um número para cada célula) em vez do sistema xy usado aqui
                        if(clickedCells[column][line]==1){
                            console.log(column+line*clickedCells.length);
                            //@ts-ignore
                            instance.exports.colocarPeca(column+line*clickedCells.length, 2);
                        }
                        if(clickedCells[column][line]==2){
                            console.log(column+line*clickedCells.length);
                            //@ts-ignore
                            instance.exports.colocarPeca(column+line*clickedCells.length, 1);
                        }
                    }
                }
                //@ts-ignore
                let next_move = instance.exports.getBestMove(dificulty);
                let position = {x:next_move%3, y:(next_move-next_move%3)/3}
                console.log("Ai wants to play: ", position);
                handleClickedCell(position);

            });
        }, 500);
    }

    /**
     * @brief Quando o turno muda para o turno do jogador 2, realiza uma jogada da IA (se o jogador 2 é a IA)
     */
    useEffect(()=>{
        if(playerTurn==2 && playernames[1]=="AI"){
            makeAImove();
        }
    }, [playerTurn]);

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
                                    handleClickedCell={playernames[1]=="AI" && playerTurn==2?()=>{}:handleClickedCell}
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