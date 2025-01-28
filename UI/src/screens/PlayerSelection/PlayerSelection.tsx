import { useEffect, useState } from "react";
import "./PlayerSelection.css";
import { PlayerBanner } from "../../components/PlayerBanner/PlayerBanner";
import { useNavigate } from "react-router-dom";

//import WebAssemblyBinary from "../../../cpp/wasm/teste.wasm?init";


export interface playerType{
    playerNick:string;
    playerName:string;
    score?:{
        gameName:string,
        wins:number,
        ties:number,
        losses:number
    }[];
}


export const PlayerSelection = () => {
    const [playerList, setPlayerList] = useState<playerType[]>([]);
    const [playerNumber, setPlayerNumber] = useState(1);
    const [player1, setPlayer1] = useState<playerType>();

    const navigate = useNavigate();

    const handleCreatePlayer = (playerNick:string, playerName:string) => {
        // @ts-ignore
        let updatedPlayerList = JSON.parse(localStorage.getItem("players"));
        //doesnt allow players with empty names or nickames
        if(playerName=="" || playerNick==""){
            alert("Por favor, preencha o nome e o apelido do jogador!");
            return false;
        }
        //doesnt allow players with the same nickname
        let samenickname = false;
        // @ts-ignore
        updatedPlayerList.forEach((player)=>{
            if(player.playerNick==playerNick){
                samenickname = true;
            }
        })
        if(samenickname){
            alert("Apelido já em uso!");
            return false;
        }
        //player cant be AI
        if(playerNick=="AI"){
            alert("Esse apelido não pode ser usado!");
            return false;
        }
        //creating a new player
        updatedPlayerList.push({
            playerNick:playerNick,
            playerName:playerName,
            score:[
                {
                    gameName:"Jogo da Velha",
                    wins:0,
                    ties:0,
                    losses:0
                },
                {
                    gameName:"Ligue Quatro",
                    wins:0,
                    ties:0,
                    losses:0,
                },
                {
                    gameName:"Reversi",
                    wins:0,
                    ties:0,
                    losses:0,
                },
            ]
        });
        //saving new players to local storage
        console.log(updatedPlayerList);
        localStorage.setItem("players", JSON.stringify(updatedPlayerList));
        //rendering new players
        setPlayerList(updatedPlayerList);
        return true;
    }

    const handleSelectPlayer = (playerNick:string, playerName:string) => {
        if(playerNumber===1){
            //selecting player 1
            setPlayer1({
                playerNick:playerNick,
                playerName:playerName
            });
            //setting next player to be selected
            setPlayerNumber(2);
        }
        if(playerNumber===2){
            //selecting player 2 and navigating to game selection
            navigate("/games", {state:{player1:player1, player2:{playerNick:playerNick, playerName:playerName}}});
        }

    }

    //loading players from local storage
    useEffect(() => {
        const players = localStorage.getItem("players");
        if(players){
            if(playerNumber==2){
                setPlayerList(JSON.parse(players).filter((player)=>(player.playerNick!=player1?.playerNick)));
            }
            else{
                setPlayerList(JSON.parse(players));
            }
        }
        /*WebAssemblyBinary().then((instance)=>{
            console.log(instance.exports.play(1, 1));
            console.log(instance.exports.play(1, 2));
            console.log(instance.exports.play(1, 3));
        });*/
    }, [playerNumber, navigate]);

    return (
        <div className="playerselectionbody">
            <h1 className="screentittle">Selecione o jogador {playerNumber}</h1>
            <div className="playerbannerdisplay">
                <ul style={{display:"flex", flexDirection:"row", paddingBottom:"20px", overflow:"visible"}}>
                    {playerList.map((item)=>(
                        <PlayerBanner
                            playerName={item.playerName}
                            playerNick={item.playerNick}
                            score={item.score}
                            handleSelectPlayer={handleSelectPlayer}
                            key={item.playerNick}
                        />
                    ))}
                    <PlayerBanner 
                        playerName="Novo Jogador" 
                        playerNick="Novo Jogador" 
                        playerType="new"
                        handleSelectPlayer={handleCreatePlayer}
                    />
                </ul>
            </div>
        </div>
    );
}