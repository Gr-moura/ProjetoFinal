import { useEffect, useState } from "react";
import "./PlayerSelection.css";
import { PlayerBanner } from "../../components/PlayerBanner/PlayerBanner";
import { useNavigate } from "react-router-dom";


/**
 * @interface playerType
 * @brief Define o tipo de um jogador.
 * @property {string} playerNick Apelido do jogador.
 * @property {string} playerName Nome do jogador.
 * @property {Array<{gameName: string, wins: number, ties: number, losses: number}>} score Pontuação do jogador em diferentes jogos.
 */
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


/**
 * @brief Componente de seleção de jogadores.
 * @return {JSX.Element} Retorna o componente de seleção de jogadores.
 */
export const PlayerSelection = () => {
    const [playerList, setPlayerList] = useState<playerType[]>([]);
    const [playerNumber, setPlayerNumber] = useState(1);
    const [player1, setPlayer1] = useState<playerType>();

    const navigate = useNavigate();

    /**
     * @brief Cria um novo jogador e o adiciona à lista de jogadores e ao localStorage.
     * @param {string} playerNick Apelido do jogador.
     * @param {string} playerName Nome do jogador.
     * @return {boolean} Retorna `true` se o jogador foi criado com sucesso, caso contrário `false`.
     */
    const handleCreatePlayer = (playerNick:string, playerName:string) => {
        // @ts-ignore
        let updatedPlayerList = JSON.parse(localStorage.getItem("players"));
        // Não permite jogadores com nome ou apelido vazio
        if(playerName=="" || playerNick==""){
            alert("Por favor, preencha o nome e o apelido do jogador!");
            return false;
        }
        // Não permite jogadores com o mesmo apelido
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
        // O jogador não pode ser "AI"
        if(playerNick=="AI"){
            alert("Esse apelido não pode ser usado!");
            return false;
        }
        // Criando um novo jogador
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
        // Salvando novo jogador no localStorage
        console.log(updatedPlayerList);
        localStorage.setItem("players", JSON.stringify(updatedPlayerList));
        // Renderizando novos jogadores na tela - atualizando lista de jogadores mostrada
        setPlayerList(updatedPlayerList);
        return true;
    }

    /**
     * @brief Seleciona um jogador e avança para a próxima etapa.
     * @param {string} playerNick Apelido do jogador selecionado.
     * @param {string} playerName Nome do jogador selecionado.
     */
    const handleSelectPlayer = (playerNick:string, playerName:string) => {
        if(playerNumber===1){
            // Selecionando jogador 1
            setPlayer1({
                playerNick:playerNick,
                playerName:playerName
            });
            // Próxima etapa: Selecionar jogador 2
            setPlayerNumber(2);
        }
        // Ao selecionar jogador 2, navega para a escolha de jogos
        if(playerNumber===2){
            navigate("/games", {state:{player1:player1, player2:{playerNick:playerNick, playerName:playerName}}});
        }

    }

    /**
     * @brief Carrega os jogadores do localStorage.
     * @details Filtra a lista de jogadores se o jogador 1 já tiver sido selecionado.
     *///loading players from local storage
    useEffect(() => {
        const players = localStorage.getItem("players");
        if(players){
            if(playerNumber==2){
                //@ts-ignore
                setPlayerList(JSON.parse(players).filter((player)=>(player.playerNick!=player1?.playerNick)));
            }
            else{
                setPlayerList(JSON.parse(players));
            }
        }
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
                    {playerNumber===2 && (<PlayerBanner
                        playerName="AI"
                        playerNick="AI"
                        playerType="nameless"
                        handleSelectPlayer={handleSelectPlayer}
                    />)}
                </ul>
            </div>
        </div>
    );
}